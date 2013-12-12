
//my_log ("Started loading our_ui.js");

	// Next Question Button {{{2
	//var nextQ = document.getElementById("nextQ");
	//EventUtil.addHandler (nextQ, "click", function(event) {
	//	alert ("nextQ");
	//	//event = EventUtil.getEvent (event);
	//	//EventUtil.preventDefault (event);
	//	var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
	//	//var data_for_cpp;
	//	//Module.setValue (data_for_cpp, "hey mr cpp function - how you doing. This is a js func calling from the dom", "i8*");
	//	//called_from_the_dom(data_for_cpp);
	//	//called_from_the_dom("hey mr cpp function - how you doing. This is a js func calling from the dom");
	//	//alert("this is the DOM brother");
	//	//console.log("submit handler called");
	//	var returnValue = serialize (question_form);
	//	//var data_for_cpp;
	//	//Module.setValue (data_for_cpp, returnValue, "i8*");
	//	called_from_the_dom(returnValue);
	//});
	// Next Question Button }}}2
	my_log ("finished nextQ");

// newNextQ Button {{{2 
var newNextQ= document.getElementById("newNextQ");
EventUtil.addHandler (newNextQ, "click", function(event) {
	//my_log ("Enter newNextQ");
	var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
	//console.log("newNextQ called");
	var returnValue = new_serialize ();
	//my_log ("new_serialize done: " + returnValue);
	called_from_the_dom(returnValue.join("|"));
});
my_log ("created submit handler function");
// newNextQ Button }}}2 

// handleStartSurveyButton  {{{2 
var return_serial_no_button = document.getElementById("btn_return_serial_no");
function handleStartSurveyButton (event)
{
	//my_log ("Enter: handleStartSurveyButton");
	var question_view = document.getElementById("question_view");
	//alert("question_view:" + question_view);
	//var attr = document.createAttribute("display");
	//attr.value = "block";
	//question_view.setAttributeNode(attr);
	var txt_serial_no = document.getElementById("txt_serial_no");
	var serial_no = txt_serial_no.value;
	//alert ("serial_no: " + serial_no);
	var re_chk_serial = /\d+/;
	var test_numeric_serial =  re_chk_serial.test(serial_no);
	if (test_numeric_serial === false) {
		alert ("Please enter a valid serial no" );
	} else {
		global_survey_related_info.serial_no = serial_no;
	}
	// Sanity checks
	var all_systems_go = false;
	//alert ("global_survey_related_info: uuid" + gl)
	//my_log ("global_survey_related_info.uuid: " + global_survey_related_info.device.uuid);
	//my_log ("global_survey_related_info.latitude: " + global_survey_related_info.position.coords.latitude);
	if (
		test_numeric_serial &&
		global_survey_related_info.device && global_survey_related_info.device.uuid &&
		global_survey_related_info.position && global_survey_related_info.position.coords &&
		global_survey_related_info.fileSystemObject)  {
		question_view.style.display = "block";
		var div_serial_no = document.getElementById("div_serial_no");
		div_serial_no.style.display = "none";
		return_serial_no_button.disabled = true;
		my_log ("sanity checks passed");
		var our_path = "qscript/" +
				global_survey_related_info.device.uuid +
				"/project_name/interviewer_id/project_name_interviewer_id_" +
				serial_no +
				".dat";
		//alert ("our_path:" + our_path);
		// first try to open the file and see if it exists
		my_log("opening file:" + our_path);
		global_survey_related_info.serial_no = serial_no;
		global_survey_related_info.open_file_path = our_path;
		global_survey_related_info.fileSystemObject.root.getFile(
			our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
		//global_survey_related_info.fileSystemObject.root.getFile("qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat", null, gotFileEntry, getFileErrorHandler);
		// if successful, we need to merge in the survey data into the qnre
		// so that eval correctly returns the next question to be asked
		// otherwise open the path piecewise - constructing intermediate directories on the way
		//fileGetDir (our_path, printSuccess, false, getFileErrorHandler);
		//all_systems_go = true;
	} else {
		my_log ("cordova : sanity checks failed");
		// my_log ("global_survey_related_info.device: " + global_survey_related_info.device);
		// my_log ("global_survey_related_info.position: " + global_survey_related_info.position);
		// my_log ("global_survey_related_info.fileSystemObject: " + global_survey_related_info.fileSystemObject);
	}
	//my_log (" after sanity checks");
	var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
	if (//all_systems_go &&  
			callback_return_serial) {
		my_log("about to invoke callback_return_serial");
		//console.log("returning serial no to c++ code");
		// add check on serial no here.
		// REMOVE THESE FROM HERE LATER : NxD 18-Aug-2013
		question_view.style.display = "block";
		var div_serial_no = document.getElementById("div_serial_no");
		div_serial_no.style.display = "none";
		//return_serial_no_button.disabled = true;
		callback_return_serial (txt_serial_no.value, "");
	} else {
		my_log ("Could not find callback_return_serial in Module.cwrap");
	}
	//var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
	//callback_return_serial (serial_no);
	my_log ("Exit handleStartSurveyButton");
}
	EventUtil.addHandler (return_serial_no_button, "click", handleStartSurveyButton);
	my_log ("created handleStartSurveyButton function");
// handleStartSurveyButton  }}}2 

function analyse_page_structure (questions_obj_arr, stubs_obj_arr) {
	var result;
	if (questions_obj_arr.length == 1) {
		result = "single_question";
	} else if (questions_obj_arr.length > 1) {
		if (stubs_obj_arr.length == 1) {
			result = "grid_question";
		} else {
			result = "multiple_questions_per_page";
		}
	}
	return result;
}

function get_translation (key) {
	var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
	return language_translation_obj[key];
}

function create_single_question_title (single_question_text_obj) {
	var question_translated_text = "";
	question_translated_text += "single_question_text_obj.length: " + single_question_text_obj.question_text_arr.length;
	var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
	var t1 = 0, key = "";
	for (t1=0; t1 < single_question_text_obj.question_text_arr.length; ++t1) {
		question_translated_text += "t1 == " + t1;
		key =  single_question_text_obj.question_text_arr[t1].key[0];
		question_translated_text += "key == " + key;
		if (single_question_text_obj.question_text_arr[t1].texpr_type === "simple_text") {
			question_translated_text += language_translation_obj[key];
		}
		if (single_question_text_obj.question_text_arr[t1].texpr_type === "named_attr") {
			//question_translated_text += qnre_hi_obj[question_text_obj_arr[i].question_text_arr[t1].key[0]];
			question_translated_text += language_translation_obj[key];
		}
		if (single_question_text_obj.question_text_arr[t1].texpr_type === "nq") {
			//question_translated_text += qnre_hi_stubs_obj[question_text_obj_arr[i].question_text_arr[t1].key[0]];
			question_translated_text += language_translation_obj[key];
		}
	}
	//question_title_div.innerHTML += "<p>nxd:" + question_translated_text + "</p>";

	return question_translated_text;
}

function create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr) {
	var verbatim_file_names;
	verbatim_file_names = [];


	/*
	// hindi translation test
	if (global_survey_related_info.qnre_hi_obj) {
		alert(global_survey_related_info.qnre_hi_obj["q3_0"]);
	}
	// end of hindi translation test
	*/
	my_log ("create_multiple_questions_view: ");

	if (questions_obj_arr[0].question_type == 'video_q') {
		
		var new_question_view = "";

		new_question_view = "<p>" + questions_obj_arr[0].question_text_arr.join() + "</p>";
		new_question_view += '<div style="width:320px; margin:0 auto;"><video width="320" height="240" controls><source src="' + questions_obj_arr[0].media_url + '" type="video/mp4"></video></div>';
		document.getElementById("new_question_view").innerHTML = new_question_view;

		document.getElementById("new_question_view").getElementsByTagName("video")[0].play();
	}
	else if (questions_obj_arr[0].question_type == 'image_q') {
		
		var new_question_view = "";
		new_question_view = "<p>" + questions_obj_arr[0].question_text_arr.join() + "</p>";
		new_question_view += "<img src=\"" + questions_obj_arr[0].media_url  + "\" alt=\"Smiley face\" height=\"200\" width=\"200\">";
		document.getElementById("new_question_view").innerHTML = new_question_view;

	}
	else if (questions_obj_arr[0].question_type == 'nqq') {
		var new_question_view = "";

		for (var i=0; i<questions_obj_arr.length; i++) {
			var curr_question_obj = questions_obj_arr[i];
			
			new_question_view += "<p>" + curr_question_obj.question_text_arr[0] + "</p>";
			new_question_view += "<form id ='id_form_" + curr_question_obj.qno + "' name ='form_" + curr_question_obj.qno + "' ><fieldset data-role='controlgroup'>";			
			
			for (var j=0; j<stubs_obj_arr.length; j++) {
				if(curr_question_obj.stub_name == stubs_obj_arr[j].name) {

					for (var k=0; k<stubs_obj_arr[j].stubs.length; k++) {
						var name = "radio-choice-" + curr_question_obj.qno;
						var id = name + "-" + k;
						var text = stubs_obj_arr[j].stubs[k].stub_text;
						var value = stubs_obj_arr[j].stubs[k].stub_code;

						new_question_view += "<div><input name='" + name + "' id='" + id + "' value='" + value + "' type='radio'>";
						new_question_view += "<label for='" + id + "'>" + text + "</label></div>";
					}

					j = stubs_obj_arr.length;	//break if stub found
				}

			}

			new_question_view += "</fieldset></form>";
		}

		if (err_obj_arr[0]) {
			new_question_view +=  "<p style='color:red;'>" + err_obj_arr.join("</p><p style='color:red;'>") + "</p>";
		}

		document.getElementById("new_question_view").innerHTML = new_question_view;
	}

	else if (questions_obj_arr[0].question_type == 'rq') {
		var new_question_view = "";
		if (questions_obj_arr.length == 1 && questions_obj_arr[0].question_text_arr.length == 1) {
			new_question_view += "<div>" + questions_obj_arr[0].question_text_arr[0] + "</div>";
			new_question_view += "<div><form id ='id_form_" + questions_obj_arr[0].qno + "' name ='form_" + questions_obj_arr[0].qno + "' >";
			//new_question_view += "<input cols='40' rows='8' id='input_" + questions_obj_arr[0].qno + "' name='input_" + questions_obj_arr[0].qno + "'></input>";			
			new_question_view += "<textarea cols='40' rows='8' id='input_" + questions_obj_arr[0].qno + "' name='input_" + questions_obj_arr[0].qno + "'></textarea>";
			new_question_view += "</form></div>";
		} else {
			var is_question_text_same = true;
			 
			for (var i=1; i<questions_obj_arr.length; i++) {
				if( questions_obj_arr[i].question_text_arr[0] != questions_obj_arr[0].question_text_arr[0]) {
					is_question_text_same = false;
					break;
				}
			}
			
			new_question_view = "<table>";
			if(is_question_text_same) {
				new_question_view += "<tr><th>" + questions_obj_arr[0].question_text_arr[0] + "</th></tr>";
			}
			for (var i=0; i<questions_obj_arr.length; i++) {
				var curr_question_obj = questions_obj_arr[i];
				if(!is_question_text_same) {
					new_question_view += "<tr><td>" + curr_question_obj.question_text_arr[0] + "</td></tr>";
				}
				new_question_view += "<tr><td>" + curr_question_obj.question_text_arr[1] + "</td>";
				new_question_view += "<td><form id ='id_form_" + curr_question_obj.qno + "' name ='form_" + curr_question_obj.qno + "' >";				
				// load previous button click response
				var prevValue = "";
				if (curr_question_obj.current_response.length) {
					prevValue = curr_question_obj.current_response[0];
				}				
				if (questions_obj_arr[i].no_mpn > 1) {
					new_question_view += "<input cols='40' rows='3' value='" + prevValue + "' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
					var verbatim_fn = "";
					verbatim_fn = global_survey_related_info.our_dir_path + "/incomplete/" +
						//questions_obj_arr[0].qno + "." + 
						curr_question_obj.qno + "." + 
						global_survey_related_info.our_file_name + ".dat";
					verbatim_file_names.push(verbatim_fn);
				} else {
					new_question_view += "<input cols='40' rows='3' type='number' value='" + prevValue + "' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
				}
				new_question_view += "</form></td></tr>";
			}
			new_question_view += "</table>";
			for (i = 0; i < verbatim_file_names.length; ++i) {
				my_log ("creating verbatim_file handles");
				global_survey_related_info.fileSystemObject.root.getFile(
					verbatim_file_names[i], {create: true}, gotVerbatimFileEntry, getFileErrorHandler);
			}
		}


		if (err_obj_arr[0]) {
			new_question_view +=  "<p style='color:red;'>" + err_obj_arr.join("</p><p style='color:red;'>") + "</p>";
		}

		document.getElementById("new_question_view").innerHTML = new_question_view;


		//if (questions_obj_arr[0].no_mpn > 1) {
		//	var verbatim_response_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		//	global_survey_related_info.fileSystemObject.root.getFile(
		//		verbatim_response_path, {create: true}, gotVerbatimFileEntry, getFileErrorHandler);
		//}
	}
	else if (questions_obj_arr[0].question_type == 'video_capture') {
		var media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		global_survey_related_info.fileSystemObject.root.getFile(
					media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);

		var new_html ="<p>Please capture a video</p>";
		new_html += "<button onclick=\"captureVideo();\">Capture Video</button> <br>";
					//"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>";
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = new_html;
	}
	else if (questions_obj_arr[0].question_type == 'image_capture') {
		var media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		my_log ("media_capture_file_path: " + media_capture_file_path);
		//global_survey_related_info.fileSystemObject.root.getFile(
		//			media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
		var new_html = "<p>Please click a photo</p>";
		new_html +=	"<button onclick=\"capturePhoto();\">Capture Photo</button> <br>" ; 
					//"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>";
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = new_html;
	}
	else if (questions_obj_arr[0].question_type == 'audio_capture') {
		var media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		//global_survey_related_info.fileSystemObject.root.getFile(
		//			media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
		var new_html = "<p>Please record the Audio response</p>";
		new_html += "<button onclick=\"captureAudio();\">Capture Audio</button> <br>" +
					"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>";
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = new_html;

	}

	else {
		//my_log ("Enter:  create_multiple_questions_view" );
		var new_question_view = document.getElementById("new_question_view");
		//new_question_view.innerHTML = "<p>" + "from ui_create_question_form with love" + "</p>";
		new_question_view.innerHTML = "";

		var questions_view_frag = document.createDocumentFragment();
		var a_question_div, question_title_div, question_stubs_div, curr_question_obj, question_stubs_form, question_stubs_form_fieldset;
		for (var i = 0; i < questions_obj_arr.length;  ++i) {
			curr_question_obj = questions_obj_arr[i];

			question_title_div = document.createElement("div");
			//question_title_div.innerHTML = "<p>" + curr_question_obj.qno + "</p>";
			//my_log ("curr_question_obj.no curr_question_obj.question_text_arr.length: " + curr_question_obj.question_text_arr.length);
			for (var j = 0; j < curr_question_obj.question_text_arr.length; ++j) {
				var question_text = curr_question_obj.question_text_arr[j];
				question_title_div.innerHTML += "<p>" + question_text + "</p>";
			}
			//my_log ("after curr_question_obj.no curr_question_obj.question_text_arr.length: " + curr_question_obj.question_text_arr.length);
			question_stubs_div = document.createElement("div");
			//question_stubs_div.innerHTML = "<p>" + curr_question_obj.stub_name + "</p>";
			var stubs_doc_frag = get_stubs_display_view (curr_question_obj, stubs_obj_arr);
			//question_stubs_div.innerHTML = "<p>" + curr_question_obj.stub_name + "</p>";
			question_stubs_div.innerHTML = "";
			//question_stubs_div.innerHTML += "<p>" + stubs_doc_frag + "</p>";
			question_stubs_div.appendChild (stubs_doc_frag);
			question_stubs_form = document.createElement("form");
			question_stubs_form.name = "form_" + curr_question_obj.qno;
			question_stubs_form.id = "id_form_" + curr_question_obj.qno;
			question_stubs_form_fieldset = document.createElement("fieldset");
			question_stubs_form_fieldset.setAttribute("data-role","controlgroup");
			question_stubs_form_fieldset.appendChild(question_stubs_div);
			question_stubs_form.appendChild(question_stubs_form_fieldset);
			// my_log ("stubs_doc_frag: " + stubs_doc_frag);
			// my_log ("question_stubs_div: " + question_stubs_div);
			// my_log ("question_stubs_div.outerHTML: " + question_stubs_div.outerHTML);
			// my_log ("question_stubs_div.outerText: " + question_stubs_div.outerTEXT);
			
			a_question_div = document.createElement("div");
			//my_log ("after create a_question_div");
			//a_question_div.innerHTML = question_title_div.outerHTML + question_stubs_div.outerHTML;
			a_question_div.appendChild (question_title_div);
			a_question_div.appendChild (question_stubs_form);
			questions_view_frag.appendChild(a_question_div);
		}
		new_question_view.appendChild (questions_view_frag);
		//$( '#stubs_form_div' ).trigger( 'create' );
		if (err_obj_arr[0]) {
			alert("err");
			//new_question_view +=  "<p style='color:red;'>" + err_obj_arr.join("</p><p style='color:red;'>") + "</p>";
		}
		$( '#new_question_view' ).trigger( 'create' );
		//my_log ("Exit: create_multiple_questions_view");
	}
	$( '#new_question_view' ).trigger( 'create' );

	window.scrollTo(0, 0);		// scroll to top
}

	/*
	function create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr) {
		my_log ("Enter:  create_multiple_questions_view" );
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = "<p>" + "from ui_create_question_form with love" + "</p>";

		var questions_view_frag = document.createDocumentFragment();
		var a_question_div, question_title_div, question_stubs_div, curr_question_obj, question_stubs_form;
		for (var i = 0; i < questions_obj_arr.length;  ++i) {
			curr_question_obj = questions_obj_arr[i];

			question_title_div = document.createElement("div");
			question_title_div.innerHTML = "<p>" + curr_question_obj.qno + "</p>";
			my_log ("curr_question_obj.no curr_question_obj.question_text_arr.length: " + curr_question_obj.question_text_arr.length);
			for (var j = 0; j < curr_question_obj.question_text_arr.length; ++j) {
				var question_text = curr_question_obj.question_text_arr[j];
				question_title_div.innerHTML += "<p>" + question_text + "</p>";
			}
			my_log ("after curr_question_obj.no curr_question_obj.question_text_arr.length: " + curr_question_obj.question_text_arr.length);
			question_stubs_div = document.createElement("div");
			//question_stubs_div.innerHTML = "<p>" + curr_question_obj.stub_name + "</p>";
			var stubs_doc_frag = get_stubs_display_view (curr_question_obj, stubs_obj_arr);
			question_stubs_div.innerHTML = "<p>" + curr_question_obj.stub_name + "</p>";
			//question_stubs_div.innerHTML += "<p>" + stubs_doc_frag + "</p>";
			question_stubs_div.appendChild (stubs_doc_frag);
			question_stubs_form = document.createElement("form");
			question_stubs_form.name = "form_" + curr_question_obj.qno;
			question_stubs_form.id = "id_form_" + curr_question_obj.qno;
			question_stubs_form.appendChild (question_stubs_div);
			// my_log ("stubs_doc_frag: " + stubs_doc_frag);
			// my_log ("question_stubs_div: " + question_stubs_div);
			// my_log ("question_stubs_div.outerHTML: " + question_stubs_div.outerHTML);
			// my_log ("question_stubs_div.outerText: " + question_stubs_div.outerTEXT);
			
			a_question_div = document.createElement("div");
			my_log ("after create a_question_div" );
			//a_question_div.innerHTML = question_title_div.outerHTML + question_stubs_div.outerHTML;
			a_question_div.appendChild (question_title_div);
			a_question_div.appendChild (question_stubs_form);
			questions_view_frag.appendChild(a_question_div);
		}
		new_question_view.appendChild (questions_view_frag);
		//$( '#stubs_form_div' ).trigger( 'create' );
		$( '#new_question_view' ).trigger( 'create' );
		my_log ("Exit: create_multiple_questions_view");
	}
	*/

	function create_grid_questions_view (questions_obj_arr, stubs_obj_arr) {
		my_log ("Enter: create_multiple_questions_view" );
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = "<p>" + "from ui_create_question_form with love" + "</p>";
		$( '#stubs_form_div' ).trigger( 'create' );
		my_log ("Exit: create_multiple_questions_view"  );
	}


function get_stubs_display_view (question_obj, stubs_obj_arr) {
	//my_log ("Enter: get_stubs_display_view: question_obj.no_mpn" + question_obj.no_mpn);
	question_type = question_obj.question_type;
	//my_log ("After question_type.question_type");
	var doc_frag2 = document.createDocumentFragment();
	if (question_type === "nq") {
		//var res2 = JSON.parse(json_rep2);
		var res2 = null;
		for (var tmp_i = 0; tmp_i < stubs_obj_arr.length; ++tmp_i) {
			if (stubs_obj_arr[tmp_i].name == question_obj.stub_name) {
				res2 = stubs_obj_arr[tmp_i];
				break;
			}
		}
		if (res2 === null) {
			my_log ("Internal error in survey: did not find stubs for :" + question_obj.qno);
		}
		//my_log ("assigned res2 , length:" + res2.stubs.length);
		//alert (res2.name);
		//alert (res2.stubs);
		var my_li = null;
		for (var i=0; i<res2.stubs.length;  ++i) {
			//my_log ("looping i = " + i);
			if (res2.stubs[i].mask == 1) {
				var input   = document.createElement("input");
				//my_log ("after document.createElement i = " + i);
				if (question_obj.no_mpn == 1) {
					input.type  = "radio";
				} else {
					input.type  = "checkbox";
					input.style.class="custom";
				}
				//my_log ("created input i = " + i);
				//input.name  = "stub_response";
				input.name  = "radio-choice";
				input.value = res2.stubs[i].stub_code;
				//my_log ("after setting input.value i = " + i);
				//var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
				var id_text = res2.name + res2.stubs[i].stub_code ;
				//alert("id_text: " + id_text);
				input.id  = id_text;
				//alert ("id_text:" + id_text);
				var input_label   = document.createElement("label");
				//input_label.innerHTML = res2.stubs[i].stub_text;
				input_label.innerHTML = "<table><tr><td nowrap>" + res2.stubs[i].stub_text + "</td>";
				if (res2.stubs[i].url_image.length > 0) {
					input_label.innerHTML += "<td><img src='" + res2.stubs[i].url_image + "'/></td>";
				}
				input_label.innerHTML += "</tr></table>";
				input_label.setAttribute("for", id_text);
				my_li = document.createElement("span");
				my_li.appendChild(input);
				my_li.appendChild(input_label);
				doc_frag2.appendChild(my_li);

				/*if (res2.stubs[i].url_image.length > 0) {
					var img = new Image();
					img.src =  res2.stubs[i].url_image;
					my_li.appendChild (img);
				}*/
				//img.src =  "http://www.example.com/test?name=Nicholas";
			}
		}

		//clear_prev_node_sub_child (stubs_form_div);

		//stubs_form_div.appendChild(doc_frag2);



	} else {
		var input_text = document.createElement("input");
		input_text.type  = "text";
		doc_frag2.appendChild(input_text);
		//clear_prev_node_sub_child (stubs_form_div);
		//stubs_form_div.appendChild(doc_frag2);
	}
	// move this to the function that renders the view
	// $( '#stubs_form_div' ).trigger( 'create' );
	//my_log ("Exit: get_stubs_display_view");
	return doc_frag2;
}


function ui_create_question_form (questions_obj_arr, stubs_obj_arr, err_obj_arr) {
	//my_log ("Entered: ui_create_question_form questions_obj_arr:" + questions_obj_arr);
	//my_log ("document.forms.length: " + document.forms.length);

	var result = analyse_page_structure (questions_obj_arr, stubs_obj_arr);
	if (result == "single_question") {
		create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr);
	} else if (result == "multiple_questions_per_page") {
		create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr);
	} else if (result == "grid_question") {
		create_grid_questions_view (questions_obj_arr, stubs_obj_arr);
	} else {
		my_log ("unhandled case - analyse_page_structure");
	}
	//my_log ("Exited: ui_create_question_form stubs_obj_arr:" + stubs_obj_arr);
}


function serialize (form, my_question_obj) {
	//my_log("Enter: serialize: my_question_obj" + my_question_obj);
	var parts = new Array();
	var field = null;
	for (var i=0; i < form.elements.length; ++i ) {
		field = form.elements[i];
		switch (field.type) {
		case "radio":
			//my_log ("case radio");
			if (field.checked) {
				parts.push(field.value);
			}
		break;
		case "checkbox":
			//my_log ("case checkbox");
			if (field.checked) {
				parts.push(field.value);
			}
		break;
		case "number":
		case "text":
		case "textarea":
			//my_log ("case text: nxd");
			/*
			if (global_survey_related_info.question_type != "nq" &&
				global_survey_related_info.no_mpn == 1) {
				parts.push(field.value);
			} else {
				my_log ("trying to save verbatim file: verbatim is:" + field.value);
				parts.push("96"); // dummy value
				// Initiate file saving here
				// Comment out - when running in browser
				// enable for cordova
				//global_survey_related_info.current_verbatim_data = field.value;
				//if (save_verbatim_data) {
				//	my_log ("save_verbatim_data:" + save_verbatim_data);
				//}
				//if (fail_to_write_file) {
				//	my_log ("fail_to_write_file:" + fail_to_write_file);
				//}
				//my_log ("global_survey_related_info.verbatim_data_file_handle:" + global_survey_related_info.verbatim_data_file_handle);
				//if (global_survey_related_info.verbatim_data_file_handle) {
				//	my_log ("verbatim_data_file_handle:" + global_survey_related_info.verbatim_data_file_handle);
				//	my_log ("testing for createWriter:");
				//	if (global_survey_related_info.verbatim_data_file_handle.createWriter) {
				//		my_log ("global_survey_related_info.verbatim_data_file_handle.createWriter: exists");
				//	} else {
				//		my_log ("global_survey_related_info.verbatim_data_file_handle.createWriter: does not exist");
				//	}
				//	my_log ("after createWriter:");
				//} else {
				//	my_log ("verbatim_data_file_handle: is null");
				//}
				//global_survey_related_info.verbatim_data_file_handle.createWriter (save_verbatim_data, fail_to_write_file);
			}
			*/
			if (my_question_obj.question_type === "rq") {
				if ( my_question_obj.no_mpn == 1) {
					parts.push(field.value);
				} else {
					my_log ("trying to save verbatim file: verbatim is:" + field.value);

					//parts.push(field.value); // dummy value
					parts.push("96"); // dummy value
					// Initiate file saving here
					/* Comment out - when running in browser
					 * enable for cordova*/
					var the_verbatim_data = field.value;
					my_log ("the_verbatim_data: " + the_verbatim_data);
					/* : old way : 5-dec-2013
					global_survey_related_info.current_verbatim_data = field.value;
					if (save_verbatim_data) {
						//my_log ("save_verbatim_data:" + save_verbatim_data);
					}
					if (fail_to_write_file) {
						//my_log ("fail_to_write_file:" + fail_to_write_file);
					}
					//my_log ("global_survey_related_info.verbatim_data_file_handle:" + global_survey_related_info.verbatim_data_file_handle);
					//global_survey_related_info.verbatim_data_file_handle.createWriter (save_verbatim_data, fail_to_write_file);
					global_survey_related_info.current_verbatim_data_file_fileEntry.createWriter (save_verbatim_data, fail_to_write_file);
					*/
					//global_survey_related_info.verbatim_data_arr.push(the_verbatim_data);
				}
			}
		break;
		}
	}
	var return_value = parts.join(" ");
	my_log("Exiting: serialize return_value:" + return_value);
	//return parts.join(" ");
	return return_value;
}


function new_serialize () {
	//my_log("Enter: new_serialize");
	var form_data_arr = [];
	var i = 0;
	for (i = 0; i < document.forms.length; ++i) {
		var form_serialized_data = serialize (document.forms[i], global_survey_related_info.questions_obj_arr[i]);
		//console.log ("form_serialized_data:" );
		my_log ("form_serialized_data:" + form_serialized_data);
		form_data_arr.push (form_serialized_data);
		my_log ("finished loop iter i== " + i);
	}
	my_log("Exit: new_serialize");
	return form_data_arr;
}
	/*
*/


my_log ("Finished loading our_ui.js");
