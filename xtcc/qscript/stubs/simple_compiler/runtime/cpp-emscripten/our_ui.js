// geolocation timer global variable
var geolocationTimer = 60;

//my_log ("Started loading our_ui.js");
//

function check_all_questions_answered_or_allow_blank() {
	var i = 0, len = global_survey_related_info.questions_obj_arr.length;
	var blank_questions = [];
	for ( i =  0; i < len; ++i ) {
		var q =  global_survey_related_info.questions_obj_arr[0];
		if (q.question_type === 'geocode_gmapv3') {
			if (q.allow_blank === true) {
				my_log ("q.allow_blank === true");
			} else /*if (q.allow_blank === false) */ {
				my_log ("q.allow_blank === false");
				if (global_survey_related_info.geocode_question_data[q.qno] === undefined) {
					blank_questions.push(q.qno);
				} else {
				}
			}
		}
	}
	return blank_questions;
}


/* newNextQ Button {{{2 */
var newNextQ= document.getElementById("newNextQ");
EventUtil.addHandler (newNextQ, "click", function(event) {
	my_log ("Enter newNextQ");
	var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
	//console.log("newNextQ called");
	var ui_front_end_check_blank_q = check_all_questions_answered_or_allow_blank();
	if (ui_front_end_check_blank_q.length === 0) {
		var returnValue = new_serialize ();
		//my_log ("new_serialize done: " + returnValue);
		called_from_the_dom(returnValue.join("|"));
	} else {
		my_log ("report errors that some questions are blank n = : " + ui_front_end_check_blank_q.length);
	}
});
//my_log ("created newNextQ handler function");
/* newNextQ Button }}}2 */

/* prevQ Button {{{2 */
var prevQ= document.getElementById("prevQ");
EventUtil.addHandler (prevQ, "click", function(event) {
	my_log ("Enter prevQ");
	var navigate_previous = Module.cwrap ('navigate_previous', 'void', ['string']);
	//console.log("prevQ called");
	my_log ("navigate_previous: " + navigate_previous);
	navigate_previous ("dummy data");
});
//my_log ("created prevQ handler function");
/* prevQ Button }}}2 */

/* handleStartSurveyButton  {{{2 */
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
	//alert(!(global_survey_related_info.position));
	if($("#selectGPS").val()=="on" && !(global_survey_related_info.position)) {
		alert("Cannot proceed without GPS");
	}
	//global_survey_related_info.position && global_survey_related_info.position.coords &&
	else if ( test_numeric_serial && global_survey_related_info.device && global_survey_related_info.device.uuid && global_survey_related_info.fileSystemObject) {
		question_view.style.display = "block";
		var div_serial_no = document.getElementById("div_serial_no");
		div_serial_no.style.display = "none";
		document.getElementById("newNextQDiv").style.display = "block";			// enable next button
		return_serial_no_button.disabled = true;
		//my_log ("sanity checks passed");

		global_survey_related_info.our_file_name += serial_no;					// append serial no to generated filename
		var our_dir_path 	= global_survey_related_info.our_dir_path + "/incomplete";
		MakePathDir (our_dir_path);
		
		var our_path 		= global_survey_related_info.our_dir_path + "/incomplete/" + global_survey_related_info.our_file_name + ".dat";
		var our_gps_path 	= global_survey_related_info.our_dir_path + "/incomplete/" + global_survey_related_info.our_file_name + ".gps";
		//alert ("our_path:" + our_path);
		// first try to open the file and see if it exists
		//my_log("opening file:" + our_path);
		global_survey_related_info.serial_no = serial_no;
		global_survey_related_info.open_file_path = our_path;
		global_survey_related_info.fileSystemObject.root.getFile(
			our_path, {create: true}, gotFileEntry, getFileErrorHandler);
		//global_survey_related_info.fileSystemObject.root.getFile("qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat", null, gotFileEntry, getFileErrorHandler);
		// if successful, we need to merge in the survey data into the qnre
		// so that eval correctly returns the next question to be asked
		// otherwise open the path piecewise - constructing intermediate directories on the way
		//fileGetDir (our_path, printSuccess, false, getFileErrorHandler);
		global_survey_related_info.fileSystemObject.root.getFile(
			our_gps_path, {create: true, exclusive: false}, gotGPSFileEntry, getFileErrorHandler);
		// write gps file
		//navigator.geolocation.getCurrentPosition(fnGPSLocaterFound, fnGPSLocaterFailed,{timeout:180000});
		geolocationTimer = setInterval(function(){
			
			navigator.geolocation.getCurrentPosition(fnGPSLocaterFound, fnGPSLocaterFailed,{timeout:180000});
			global_survey_related_info.fileSystemObject.root.getFile(our_gps_path, {create: true, exclusive: false}, gotGPSFileEntry, getFileErrorHandler);

		},geolocationTimer*1000);		// write gps after every 60 seconds
		createCommonDirectories();		// create common directories
		//all_systems_go = true;
	} else {
		my_log ("cordova : sanity checks failed");
		// my_log ("global_survey_related_info.device: " + global_survey_related_info.device);
		// my_log ("global_survey_related_info.position: " + global_survey_related_info.position);
		// my_log ("global_survey_related_info.fileSystemObject: " + global_survey_related_info.fileSystemObject);
	}
	//my_log (" after sanity checks");	
	//var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
	//callback_return_serial (serial_no);
	//my_log ("Exit handleStartSurveyButton");
}
EventUtil.addHandler (return_serial_no_button, "click", handleStartSurveyButton);
//my_log ("created handleStartSurveyButton function");
/* handleStartSurveyButton  }}}2 */

function handleStartSurveyButtonBrowserOnly (event) {
	var question_view = document.getElementById("question_view");
	var txt_serial_no = document.getElementById("txt_serial_no");
	var serial_no = txt_serial_no.value;
	//alert ("serial_no: " + serial_no);
	var re_chk_serial = /\d+/;
	var test_numeric_serial =  re_chk_serial.test(serial_no);
	var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
	if (test_numeric_serial === false) {
		alert ("Please enter a valid serial no");
	} else {
		question_view.style.display = "block";
		var div_serial_no = document.getElementById("div_serial_no");
		div_serial_no.style.display = "none";
		//return_serial_no_button.disabled = true;
		document.getElementById("newNextQDiv").style.display = "block";
		callback_return_serial (txt_serial_no.value, "");
	}
}
//EventUtil.addHandler (return_serial_no_button, "click", handleStartSurveyButtonBrowserOnly);

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

function create_single_question_title_simple (single_question_obj) {
	//my_log ("Enter: create_single_question_title_simple");
	var the_simple_q_text = single_question_obj.question_text_arr.join();
	//my_log ("the_simple_q_text: " + the_simple_q_text);
	return single_question_obj.question_text_arr.join();
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
	if (global_survey_related_info.verbatim_text_box_id_arr === undefined) {
		global_survey_related_info.verbatim_text_box_id_arr = [];
	}
	global_survey_related_info.verbatim_text_box_id_arr = [];

	if (global_survey_related_info.address_fileEntry_arr === undefined) {
		// 1st time creation - this is useless, just 
		// marks a point in the code where we add this to the 
		// global
		global_survey_related_info.address_fileEntry_arr = [];
	}
	if (global_survey_related_info.geocode_fileEntry_arr === undefined) {
		global_survey_related_info.geocode_fileEntry_arr = [];
	}
	// reset array to null each time
	global_survey_related_info.address_fileEntry_arr = [];
	global_survey_related_info.geocode_fileEntry_arr = [];

	/*
	// hindi translation test
	if (global_survey_related_info.qnre_hi_obj) {
		alert(global_survey_related_info.qnre_hi_obj["q3_0"]);
	}
	// end of hindi translation test
	*/
	//my_log ("create_multiple_questions_view: ");

	if (questions_obj_arr[0].question_type === 'geocode_gmapv3') {
		var geocode_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "_geocode" + "." + global_survey_related_info.our_file_name + ".dat";
		var address_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "_address" + "." + global_survey_related_info.our_file_name + ".dat";

		global_survey_related_info.fileSystemObject.root.getFile(
					geocode_capture_file_path, {create: true}, gotGeocodeFileEntry, getFileErrorHandler);
		global_survey_related_info.fileSystemObject.root.getFile(
					address_capture_file_path, {create: true}, gotAddressFileEntry, getFileErrorHandler);
		my_log ("case geocode_gmapv3");
		//var new_question_view = "The humble beginnings of a geocode question";
		var new_question_view = document.getElementById("new_question_view");
		// Load the script first
		//var geocode_gmap_v3_script = document.createElement("script");
		//geocode_gmap_v3_script.type = "text/javascript";
		//geocode_gmap_v3_script.src = "https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false";
		//document.body.appendChild(geocode_gmap_v3_script);
		//my_log ("case script has been added to body");
		// Now create the div node and put it into the DOM tree
		var map_div = document.createElement("div");
		map_div.id = "map-canvas";
		//map_div.style="width:500px;height:400px;"
		map_div.style.width="500px";
		map_div.style.height="400px";
		var text_div = document.createElement("div");
		text_div.id = "test_text_div";
		text_div.innerHTML = "<p>The humble beginnings of a geocode question</p>";
		new_question_view.appendChild (map_div);
		new_question_view.appendChild (text_div);

		// Address
		var addr_div = document.createElement("div");
		addr_div.id = "addr_info";
		var addr1 = document.createElement("input");
		addr1.id = "addr1";
		addr1.type = "text";
		addr1.placeholder = "addr1";
		var addr2 = document.createElement("input");
		addr2.id = "addr2";
		addr2.type = "text";
		addr2.placeholder = "addr2";
		var city = document.createElement("input");
		city.id = "city";
		city.type = "text";
		city.placeholder = "city";
		var pin = document.createElement("input");
		pin.id = "pin";
		pin.type = "text";
		pin.placeholder = "pin";
		var geocode_button = document.createElement("input");
		geocode_button.type = "button";
		geocode_button.value = "GeoCode";
		global_survey_related_info.current_geocode_question = questions_obj_arr[0].qno;
		my_log ("set current_geocode_question");
		if (global_survey_related_info.geocode_question_data === undefined) {
			global_survey_related_info.geocode_question_data = { };
			my_log ("created global_survey_related_info.geocode_question_data object");
		}
		// later on - load the data from a file and pre-load it here instead of doing this
		global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question] = undefined;
		my_log ("set current_geocode_question data to undefined");
		EventUtil.addHandler (geocode_button, "click", geocodeAddress);
		addr_div.appendChild(addr1);
		addr_div.appendChild(addr2);
		addr_div.appendChild(city);
		addr_div.appendChild(pin);
		addr_div.appendChild(geocode_button);

		var q_form = document.createElement("form");
		q_form.id = "id_form_" + questions_obj_arr[0].qno;
		q_form.name = "form_" + questions_obj_arr[0].qno;
		q_form.appendChild(addr_div);

		new_question_view.appendChild(q_form);
		// Now initialize the map - otherwise the call to getElementById in initialize_gmap would fail
		// as map-canvas div would not be present
		initialize_gmap();
		//var map_question_view_frag = document.createDocumentFragment();
		//new_question_view.appendChild (map_question_view_frag);

		//document.getElementById("new_question_view").innerHTML = new_question_view;
		
	} else if (questions_obj_arr[0].question_type == 'video_q') {
		
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
			var curr_question_obj = questions_obj_arr[0];
			new_question_view += "<div>" + questions_obj_arr[0].question_text_arr[0] + "</div>";
			new_question_view += "<div><form id ='id_form_" + questions_obj_arr[0].qno + "' name ='form_" + questions_obj_arr[0].qno + "' >";
			//new_question_view += "<input cols='40' rows='8' id='input_" + questions_obj_arr[0].qno + "' name='input_" + questions_obj_arr[0].qno + "'></input>";			
			new_question_view += "<textarea cols='40' rows='8' id='input_" + questions_obj_arr[0].qno + "' name='input_" + questions_obj_arr[0].qno + "'></textarea>";
			new_question_view += "</form></div>";
			if (questions_obj_arr[0].no_mpn > 1) {
				//my_log (" case single no_mpn > 1 i.e. verbatim ");
				global_survey_related_info.verbatim_data_file_fileEntry_arr  = [];
				var verbatim_fn = "";
				verbatim_fn = global_survey_related_info.our_dir_path + "/incomplete/" +
					curr_question_obj.qno + "." + 
					global_survey_related_info.our_file_name + ".dat";
				verbatim_file_names.push(verbatim_fn);
				global_survey_related_info.verbatim_text_box_id_arr.push("input_" + curr_question_obj.qno);
			}
		} else {
				global_survey_related_info.verbatim_data_file_fileEntry_arr  = [];
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
				//new_question_view += "<tr><td>" + curr_question_obj.question_text_arr[1] + "</td>";
				new_question_view += "<tr>";  
				if (curr_question_obj.question_text_arr.length > 1) {
					//new_question_view += "<tr><td>" + curr_question_obj.question_text_arr[1] + "</td>";
					new_question_view += "<td>";  
					for (var j = 1; j <  curr_question_obj.question_text_arr.length; ++j) {
						new_question_view += curr_question_obj.question_text_arr[j]; 
					}
					new_question_view += "</td>";
				}
				new_question_view += "<td><form id ='id_form_" + curr_question_obj.qno + "' name ='form_" + curr_question_obj.qno + "' >";				
				// load previous button click response
				var prevValue = "";
				if (curr_question_obj.current_response.length) {
					prevValue = curr_question_obj.current_response[0];
				}				
				if (questions_obj_arr[i].no_mpn > 1) {
					//new_question_view += "<input cols='40' rows='3' value='" + prevValue + "' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
					new_question_view += "<input cols='40' rows='3' value='' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
					var verbatim_fn = "";
					verbatim_fn = global_survey_related_info.our_dir_path + "/incomplete/" +
						//questions_obj_arr[0].qno + "." + 
						curr_question_obj.qno + "." + 
						global_survey_related_info.our_file_name + ".dat";
					verbatim_file_names.push(verbatim_fn);
					global_survey_related_info.verbatim_text_box_id_arr.push("input_" + curr_question_obj.qno);
				} else {
					new_question_view += "<input cols='40' rows='3' type='number' value='" + prevValue + "' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
				}
				new_question_view += "</form></td></tr>";
			}
			new_question_view += "</table>";
		}


		if (err_obj_arr[0]) {
			new_question_view +=  "<p style='color:red;'>" + err_obj_arr.join("</p><p style='color:red;'>") + "</p>";
		}

		document.getElementById("new_question_view").innerHTML = new_question_view;

		//my_log ("verbatim_file_names.length: " + verbatim_file_names.length);
		// This is really complicated - refer to Professional Javascript : Nicholas C Zakas -
		// Chapter 7
		var function_result_arr = [];
		for (var i = 0; i < verbatim_file_names.length; ++i) {
			function_result_arr[i] = function (index) {
				return function (fileEntry) {
					//my_log ("gotVerbatimFileEntry index: " + index);

					function gotVerbatimFile(file) {
						var reader = new FileReader();
						reader.onloadend = function(evt) {
							//my_log ("Read verbatim data: " + evt.target.result);
							//my_log ("global_survey_related_info.current_verbatim_index: " + global_survey_related_info.current_verbatim_index);
							//my_log ("gotVerbatimFile index: " + index);
							var verb_text_box = document.getElementById( global_survey_related_info.verbatim_text_box_id_arr[
									//global_survey_related_info.current_verbatim_index
									index ]);
							if (verb_text_box) {
								verb_text_box.value = evt.target.result;
							}
						//	console.log(evt.target.result);
						};
						reader.readAsText(file);
					}
					

					//my_log("Enter: gotVerbatimFileEntry");
					if (global_survey_related_info.verbatim_data_file_fileEntry_arr === undefined) {
						global_survey_related_info.verbatim_data_file_fileEntry_arr  = [];
					} else {
						my_log ("global_survey_related_info.verbatim_data_file_fileEntry_arr.length: " + global_survey_related_info.verbatim_data_file_fileEntry_arr.length);
					}
					//global_survey_related_info.current_verbatim_data_file_fileEntry = fileEntry;
					global_survey_related_info.verbatim_data_file_fileEntry_arr.push(fileEntry);
					fileEntry.file(gotVerbatimFile, getFileErrorHandler);
					//my_log ("Exit global_survey_related_info.verbatim_data_file_fileEntry_arr.length: " + global_survey_related_info.verbatim_data_file_fileEntry_arr.length);
				};
			} (i);


			//my_log ("creating verbatim_file handle: i " + i);
			global_survey_related_info.current_verbatim_index = i;
			global_survey_related_info.fileSystemObject.root.getFile(
				verbatim_file_names[i], {create: true},
				//gotVerbatimFileEntry,
				function_result_arr[i],
				getFileErrorHandler);
		}

		/*

		if (questions_obj_arr[0].no_mpn > 1) {

			var verbatim_response_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";


			global_survey_related_info.fileSystemObject.root.getFile(
				verbatim_response_path, {create: true}, gotVerbatimFileEntry, getFileErrorHandler);
		}
		*/
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
		/*
		var media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		my_log ("media_capture_file_path: " + media_capture_file_path);
		global_survey_related_info.fileSystemObject.root.getFile(
					media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
		var new_html = "<p>Please click a photo</p>";
		new_html +=	"<button onclick=\"capturePhoto();\">Capture Photo</button> <br>" ; 
					//"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>";
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = new_html;
		*/
		var new_html = "", media_capture_file_path ="", i=0;
		for (i = 0; i < questions_obj_arr.length; ++i) {
			media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[i].qno + "." + global_survey_related_info.our_file_name + ".dat";
			my_log ("media_capture_file_path: " + media_capture_file_path);
			global_survey_related_info.fileSystemObject.root.getFile(
					media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
			new_html += "<p>Please click a photo</p>";
			new_html += "<p>" + create_single_question_title_simple (questions_obj_arr[i]) + "</p>";
			new_html += "<button onclick=\"capturePhoto2("+ i +");\">Capture Photo</button> <br>"; 
		}
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = new_html;
	}
	else if (questions_obj_arr[0].question_type == 'audio_capture') {
		var media_capture_file_path = global_survey_related_info.our_dir_path + "/incomplete/" + questions_obj_arr[0].qno + "." + global_survey_related_info.our_file_name + ".dat";
		global_survey_related_info.fileSystemObject.root.getFile(
					media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
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

function create_grid_questions_view (questions_obj_arr, stubs_obj_arr) {
	/*my_log ("Enter: create_multiple_questions_view" );
	var new_question_view = document.getElementById("new_question_view");
	new_question_view.innerHTML = "<p>" + "from ui_create_question_form with love" + "</p>";
	$( '#stubs_form_div' ).trigger( 'create' );
	my_log ("Exit: create_multiple_questions_view"  );*/

	if (questions_obj_arr.length > 0) {
		var gridTable = document.createElement("div");
		gridTable.setAttribute("class","grid");

		var gridTableRows = questions_obj_arr.length;
		var gridTableColumns = stubs_obj_arr[0].stubs.length;

		for (var i = 0; i <= gridTableRows; i++) {
			var gridTableTr = document.createElement("div");
			var gridTableForm = document.createElement("form");

			for (var j = 0; j <= gridTableColumns; j++) {
				var gridTableTd = document.createElement("div");

				if (i) {
					if (j) {
						var id = questions_obj_arr[i-1].qno + "-" + stubs_obj_arr[0].stubs[j-1].stub_code;
						gridTableTd.innerHTML = '<input id="' + id + '" value="' + stubs_obj_arr[0].stubs[j-1].stub_code + '" name="radio-choice-' + i + '" type="radio">';
					}
					else {
						gridTableTd.innerHTML = questions_obj_arr[i-1].question_text_arr;
					}
				}
				else if (j) {
					gridTableTd.innerHTML = stubs_obj_arr[0].stubs[j-1].stub_text;
				}

				gridTableTr.appendChild(gridTableTd);
			}
			gridTableForm.appendChild(gridTableTr);
			gridTable.appendChild(gridTableForm);
		}

		document.getElementById("new_question_view").innerHTML = "";
		document.getElementById("new_question_view").appendChild(gridTable);
	}
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
			//my_log ("Internal error in survey: did not find stubs for :" + question_obj.qno);
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

				// load previous button click response
				for (var k = 0; k < question_obj.current_response.length; k++)
				{
					if (question_obj.current_response[k] == res2.stubs[i].stub_code) {
						input.checked = true;
						break;
					}
				}

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
					//alert(res2.stubs[i].url_image);
					var img = new Image();
					img.src =  res2.stubs[i].url_image;
					my_li.appendChild (img);
				}*/
				//img.src =  "http://www.example.com/test?name=Nicholas";
			}
		}
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
	my_log ("document.forms.length: " + document.forms.length);

	var result = analyse_page_structure (questions_obj_arr, stubs_obj_arr);
	if (result == "single_question") {
		create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr);
	} else if (result == "multiple_questions_per_page") {
		create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr);
	} else if (result == "grid_question") {
		create_grid_questions_view (questions_obj_arr, stubs_obj_arr);
	} else {
		//my_log ("unhandled case - analyse_page_structure");
	}
	//my_log ("Exited: ui_create_question_form stubs_obj_arr:" + stubs_obj_arr);
}


function serialize (form, my_question_obj) {
	//my_log("Enter: serialize");
	var parts = [];
	var field = null;
	if (global_survey_related_info.other_specify_data_arr === undefined) {
		global_survey_related_info.other_specify_data_arr = [];
	}
	global_survey_related_info.other_specify_data_arr = [];

	if (my_question_obj.question_type === "geocode_gmapv3") {
		my_log ("collecting data from geocode question");
		if (global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question] === undefined) {
			my_log ("geocoding question is blank, please geocode the location");
		} else {
			my_log ("geocoding question has data : " + global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question]);
		}
	} else {
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
				//my_log ("case text");
				if (my_question_obj.question_type === "rq") {
					if ( my_question_obj.no_mpn == 1) {
						parts.push(field.value);
					} else {
						//my_log ("trying to save verbatim file: verbatim is:" + field.value);

						//parts.push(field.value); // dummy value
						parts.push("96"); // dummy value
						// Initiate file saving here
						/* Comment out - when running in browser
						 * enable for cordova*/
						var the_verbatim_data = field.value;
						//my_log ("the_verbatim_data: " + the_verbatim_data);
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
						global_survey_related_info.verbatim_data_arr.push(the_verbatim_data);
					}
				}
			break;
			}
		}
	}

	var return_value = parts.join(" ");
	//my_log("Exiting: serialize return_value:" + return_value);
	//return parts.join(" ");
	return return_value;
}


function new_serialize () {
	//my_log ("Enter: new_serialize: global_survey_related_info.questions_obj_arr.length " +
	//		global_survey_related_info.questions_obj_arr.length);

	//my_log ("Enter: new_serialize: document.forms.length " + document.forms.length);

	if (global_survey_related_info.verbatim_data_arr === undefined) {
		global_survey_related_info.verbatim_data_arr = [];
	}
	global_survey_related_info.verbatim_data_arr = [];

	var form_data_arr = [];
	var i = 0;
	for (i = 0; i < document.forms.length; ++i) {
		var form_serialized_data = serialize (document.forms[i], global_survey_related_info.questions_obj_arr[i]);
		//console.log ("form_serialized_data:" );
		//my_log ("form_serialized_data:" + form_serialized_data);
		form_data_arr.push (form_serialized_data);
		//my_log ("form_data_arr: " + form_data_arr);
		//my_log ("finished loop iter i== " + i);
	}


	for (i = 0; i < global_survey_related_info.verbatim_data_arr.length; ++i) {
		my_log ("global_survey_related_info.verbatim_data_arr.length: " + global_survey_related_info.verbatim_data_arr.length);
		//global_survey_related_info.current_verbatim_data_file_fileEntry.createWriter (save_verbatim_data, fail_to_write_file);
		global_survey_related_info.current_verbatim_index = i;
		global_survey_related_info.verbatim_data_file_fileEntry_arr [i].createWriter (save_verbatim_data,
						fail_to_write_file);
	}

	// write geocode data if any
	if (global_survey_related_info.geocode_fileEntry_arr !== undefined ) {
		if (global_survey_related_info.geocode_fileEntry_arr.length === 1) {
			global_survey_related_info.geocode_fileEntry_arr[0].createWriter (save_geocode_data,
					fail_to_write_file);
			global_survey_related_info.address_fileEntry_arr[0].createWriter (save_address_data,
					fail_to_write_file);
		} else if (global_survey_related_info.geocode_fileEntry_arr.length === 0) {
		} else {
			my_log ("unhandled case geocode question - we are not handling multiple geocode questions in 1 page");
		}
	}

	//my_log("Exit: new_serialize");
	return form_data_arr;
}

function btnSync() {
	if(window.navigator.onLine) {		// check for internet connection
		fnMoveFiles();
	}
	else {
		alert("Internet connection is not available.");
	}
}

// diplays survey title, description and logged in user on survey page
function displayMetaData() {
	// $('#div_console_log').hide();	// hide console message 
	var projDetails = JSON.parse(window.localStorage.getItem('projDetails'));
	var div_serial_no = document.getElementById("div_serial_no");

	for (var i = 0; i < projDetails.length; i++) {
		if (projDetails[i].id == global_survey_related_info.job_name) {
			document.getElementById("survey_header").innerHTML = projDetails[i].title;
			div_serial_no.getElementsByTagName("h3")[0].innerHTML = projDetails[i].title;
			div_serial_no.getElementsByTagName("h5")[0].innerHTML = projDetails[i].description;
			break;
		}
	}
	// show logged in username
	$('#curr_loggedIn_user').html('Logged in as:<br/>' + window.localStorage.getItem('emailid'));
}

document.addEventListener ("deviceready", displayMetaData, false);

//my_log ("Finished loading our_ui.js");

// file sync code start

function fnMoveFiles() {
    //get hold of the first file
    var dirPath = global_survey_related_info.our_dir_fullPath + "/complete";
    window.resolveLocalFileSystemURI(dirPath, onSuccessResolutionOfDir, onErrorResolutionOfDir);
    //move it
    //come back to this folder and try moving the next file
}

function onSuccessResolutionOfDir(de) {
    var directoryReader = de.createReader();
    // Get a list of all the entries in the directory
    directoryReader.readEntries(onDirectoryReadSuccess, onDirectoryReadFail);
}

function onDirectoryReadFail(err) {
    alert("failed to read interviewer_id");
}

function onErrorResolutionOfDir(err) {
    //alert("resolution failed :" + err.code);
    alert("No files found.");
}

function onDirectoryReadSuccess(dirEntries) {
    var i, fl, len;
    len = dirEntries.length;
    if (len > 0) {
    uploadNotification.init(len);
        for (i = 0; i < len; i++) {
            if (dirEntries[i].isFile == true) {
                var ownCloudURI = encodeURI("http://173.230.133.34/upload.php");
                var options = new FileUploadOptions();
                options.fileKey = "file";
                options.fileName = dirEntries[i].name;
                options.mimeType = "text/plain";

	            var params = {};
	            params.dirpath = "/var/www/data/Demo/" + global_survey_related_info.job_name + "/" + global_survey_related_info.device.uuid + "/inter1/synced";
	            options.params = params;


                var ft = new FileTransfer();
                ft.upload(dirEntries[i].fullPath, ownCloudURI, onTransferSuccess, onTransferFail, options);
            }
        }
        //alert("All files are uploaded1");
    } else {
        alert("No Files Found!!");
    }
}


function onTransferSuccess(r) {
    //alert("transfer successful");
    //alert("Code = " + r.responseCode);
    //alert("Response = " + r.response);
    //alert("Sent = " + r.bytesSent);
    //var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/complete";
    var dirPath = global_survey_related_info.our_dir_fullPath + "/complete";
    var filePath = dirPath + "/" + JSON.parse(r.response).message.filename;
    //alert(filePath);
    window.resolveLocalFileSystemURI(filePath, onSuccessResolutionOfFileUpload, onTransferFail);

}

function onSuccessResolutionOfFileUpload(fe) {
	//var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/synced";
	var dirPath = global_survey_related_info.our_dir_fullPath + "/synced";
    var DirEntry = new DirectoryEntry("synced", dirPath);
    fe.moveTo(DirEntry, fe.name, onFileMoveSuccess, onTransferFail);
}

function onFileMoveSuccess(entry) {
    //alert("All Done");
    //alert(entry.fullPath);
    uploadNotification.uploaded();
}

function onTransferFail(err) {
	uploadNotification.notUploaded();
    //alert("failed to move file");
    //alert("An error has occurred: Code = " + err.code);
    //alert("upload error source " + err.source);
    //alert("upload error target " + err.target);
}

// file synn code end

// gps code start
$("#selectGPS").change(function(){

    if($("#selectGPS").val()=="on")
    {
        //$("#btn_return_serial_no").attr("disabled", "disabled");
        $("#popupUndismissible").popup("open");
        navigator.geolocation.getCurrentPosition(fnGPSLocaterFound, fnGPSLocaterFailed,{timeout:180000});
    }
    else
    {
        //$("#btn_return_serial_no").removeAttr("disabled");
        $("#popupUndismissible").popup("close");
    }
});

function fnGPSLocaterFound(position)
{
    global_survey_related_info.position = position;

    //$("#btn_return_serial_no").removeAttr("disabled");
    $("#popupUndismissible").popup("close");

}

function fnGPSLocaterFailed(error)
{
	if(error.code!=2)
	{
	    alert('code: ' + error.code + '\n' +'message: ' + error.message + '\n');
	    //$("#btn_return_serial_no").removeAttr("disabled");
	    $("#popupUndismissible").popup("close");
	    $("#selectGPS").val("off").slider("refresh");
	}
}
//gps code end

// this function will create required common directories
function createCommonDirectories() {
	var entryPath = global_survey_related_info.our_dir_fullPath;
	
	window.resolveLocalFileSystemURI(
		entryPath, 
		function(fileSystem) {
			fileSystem.getDirectory("complete", {create: true, exclusive: false}, null, null);
			fileSystem.getDirectory("synced", {create: true, exclusive: false}, null, null);
		}, 
		null
	);
}

// this will move completed surveys to complete folder
var moveToComplete = {

	// resolve full directory path
	onGetDirectorySuccess: {
		init: function() {
			var entryPath = global_survey_related_info.our_dir_fullPath + "/incomplete";
			window.resolveLocalFileSystemURI(entryPath, this.onSuccess, this.onError);
		},

		onSuccess: function(dir) {
			moveToComplete.onGetFileEntries.init(dir);
		},

		onError: function(error) {
			alert("onGetDirectorySuccess " + error.code);
		}
	},

	// get the list of all files and directories
	onGetFileEntries: {
		init: function(fileSystem) {
			var dr = fileSystem.createReader();
        	dr.readEntries(this.onSuccess, this.onError);
		},

		onSuccess: function(fileEntries) {
			moveToComplete.onFileReaderSuccess.init(fileEntries);
		},

		onError: function(error) {
			alert("onGetFileEntries " + error.code);
		}
	},

	// get list of files
	onFileReaderSuccess: {
		init: function(fileEntries) {
			for (var i = 0; i < fileEntries.length; i++) {
	        	if (fileEntries[i].isFile) {
	        		if(fileEntries[i].name.indexOf("_" + global_survey_related_info.serial_no + ".") >= 0) {
						var dirPath = global_survey_related_info.our_dir_fullPath + "/complete";
						var DirEntry = new DirectoryEntry("complete", dirPath);
						fileEntries[i].moveTo(DirEntry, fileEntries[i].name, this.onSuccess, this.onError);
	        		}
		        }
	        }
		},

		onSuccess: function(entry) {
		},

		onError:function(error) {
		}
	}
};

// this will show survey upload popup notification 
var uploadNotification = {

	success: 0,
	fail: 0,
	total: 0,

	init: function(files) {
		uploadNotification.total = files;
	},

	uploaded: function() {
		uploadNotification.success++;
		uploadNotification.update();
	},

	notUploaded: function() {
		uploadNotification.fail++;
		uploadNotification.update();
	},

	update: function() {
		var msg = "Something went wrong and we don't know what it is...";

		if(uploadNotification.success + uploadNotification.fail == uploadNotification.total) {
			if(!uploadNotification.fail) {
				msg = "All " + uploadNotification.success + " of " + uploadNotification.total + " files are uploaded successfully";
			}
			else {
				msg = uploadNotification.fail + " files are not uploaded";
			}
			$("#popupSync").html(msg);
			$("#popupSync").popup("open");
			$("#popupSync").trigger('refresh');
		}
	}
};

var geocoder;
var map;
var marker = null;
var infowindow = null ;


function initialize_gmap() {
	my_log ("Enter: initialize_gmap");
	if (global_survey_related_info.geocode_question_data === undefined) {
		global_survey_related_info.geocode_question_data = {};
	}

	if (window.google) {
		geocoder = new google.maps.Geocoder();

		my_log ("Reached here");
		var latlng = new google.maps.LatLng(-34.397, 150.644);
		var mapOptions = {
			//zoom: 8,
			//center: latlng
			center: new google.maps.LatLng(23.03, 72.58),
			zoom: 15,
			mapTypeControl: true,
			mapTypeControlOptions: {style: google.maps.MapTypeControlStyle.DROPDOWN_MENU},
			navigationControl: true,
			mapTypeId: google.maps.MapTypeId.ROADMAP
		};
		//map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
		var map_canvas = document.getElementById('map-canvas');
		if (map_canvas) {
			map = new google.maps.Map(map_canvas, mapOptions);
		} else {
			my_log ("unable to get element map_canvas: hence cannot create map");
		}
		google.maps.event.addListener(map, 'click', function() {
			if (infowindow) {
				infowindow.close();
			}
		});
		google.maps.event.addListener(map, 'click', function(event) {
		//call function to create marker
			if (marker) {
				marker.setMap(null);
				marker = null;
			}
			marker = createMarker(event.latLng, "name", "<b>Location</b><br>"+event.latLng);
		});

	} else {
		my_log ("does not have window.google");
	}

	infowindow = new google.maps.InfoWindow(
		{ 
		size: new google.maps.Size(150,50)
		});
	my_log("Exit: initialize_gmap");
}

	// A function to create the marker and set up the event window function 
function createMarker(latlng, name, html) {
	my_log ("Enter createMarker");
	var contentString = html;
	if (marker) {
		marker.setMap(null);
		marker = null;
	}
	marker = new google.maps.Marker({
		position: latlng,
		map: map,
		zIndex: Math.round(latlng.lat()*-100000)<<5
		});
	google.maps.event.addListener(marker, 'click', function() {
		my_log ("click function of map triggered");
		// =========
		//var geocode_data = results[0].geometry.location;
		//var geocode_data = latlng;
		global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question] = latlng;
		map.setCenter( latlng);
		// =========
		infowindow.setContent(contentString); 
		infowindow.open(map,marker);
	});
	google.maps.event.trigger(marker, 'click');
	my_log ("Exiting createMarker");
	return marker;
}




function geocodeAddress() {
	my_log ("Enter geocodeAddress");
	var addr1 =  document.getElementById('addr1');
	var addr2 =  document.getElementById('addr2');
	var city =  document.getElementById('city');
	var pin =  document.getElementById('pin');
	if (addr1) {
		my_log ("addr1: " + addr1.value);
	}
	if (addr2) {
		my_log ("addr2: " + addr2.value);
	}
	if (city) {
		my_log ("city: " + city.value);
	}
	if (pin) {
		my_log ("pin: " + pin.value);
	}

	//var address = document.getElementById('addr1').value +  "," +
	//	document.getElementById('addr2').value + "," +
	//	document.getElementById('city').value  + "," +
	//	document.getElementById('pincode').value;
	var address = addr1.value + "," + addr2.value + ", " + city.value + ", " + pin.value;
	global_survey_related_info.geocode_addr_data_json = 
		"{" + 
		" \"addr1\" : \"" + addr1.value + "\" " +
		",\"addr2\" : \"" + addr2.value + "\" " +
		",\"city\" : \"" + city.value + "\" " +
		",\"pin\" : \"" + pin.value + "\" " + 
		"}";
	my_log ("address: " + address);


	geocoder.geocode( { 'address': address}, function(results, status) {
		my_log ("doing the geo-coding right now");
		if (status == google.maps.GeocoderStatus.OK) {
			my_log ("position/location: " + results[0].geometry.location);
			//oldpos: var geocode_data = results[0].geometry.location;
			//oldpos: global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question] = geocode_data;
			//oldpos: map.setCenter(results[0].geometry.location);
			//marker = new google.maps.Marker({
			//	map: map,
			//	position: results[0].geometry.location
			//});
			//marker = createMarker(event.latLng, "name", "<b>Location</b><br>"+event.latLng);
			marker = createMarker(results[0].geometry.location, "name", "<b>Location</b><br>"+results[0].geometry.location);
			//google.maps.event.addListener(marker, 'click', function() {
			//	my_log ("click function of map triggered");
			//	infowindow.setContent(contentString); 
			//	infowindow.open(map,marker);
			//});
			//google.maps.event.trigger(marker, 'click');
			my_log("geocoder callback function has finished");

		} else {
			my_log('Geocode was not successful for the following reason: ' + status);
		}
	});
	my_log ("Exit geocodeAddress");
}

//google.maps.event.addDomListener(window, 'load', initialize);


my_log ("Finished loading our_ui.js");
