	// geolocation timer global variable
	var geolocationTimer = 60;
	//var geolocationTimerInterval = 8000;

	my_log ("Started loading our_ui.js : global_survey_related_info.job_name: " + global_survey_related_info.job_name);

	/* Next Question Button {{{2 */
	/*
	var nextQ = document.getElementById("nextQ");
	EventUtil.addHandler (nextQ, "click", function(event) {
		//event = EventUtil.getEvent (event);
		//EventUtil.preventDefault (event);
		var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
		//var data_for_cpp;
		//Module.setValue (data_for_cpp, "hey mr cpp function - how you doing. This is a js func calling from the dom", "i8*");
		//called_from_the_dom(data_for_cpp);
		//called_from_the_dom("hey mr cpp function - how you doing. This is a js func calling from the dom");
		//alert("this is the DOM brother");
		//console.log("submit handler called");
		var returnValue = serialize (question_form);
		//var data_for_cpp;
		//Module.setValue (data_for_cpp, returnValue, "i8*");
		called_from_the_dom(returnValue);
	});
	*/
	/* Next Question Button }}}2 */

	/* newNextQ Button {{{2 */
	var newNextQ= document.getElementById("newNextQ");
	EventUtil.addHandler (newNextQ, "click", function(event) {
		//my_log ("Enter newNextQ");
		var called_from_the_dom = Module.cwrap ('called_from_the_dom', 'void', ['string']);
		//console.log("newNextQ called");
		var returnValue = new_serialize ();
		//my_log ("new_serialize done: " + returnValue);
		called_from_the_dom(returnValue.join("|"));
	});
	//my_log ("created newNextQ handler function");
	/* newNextQ Button }}}2 */

	/* prevQ Button {{{2 */
	var prevQ= document.getElementById("prevQ");
	EventUtil.addHandler (prevQ, "click", function(event) {
		my_log ("Enter prevQ");
		var navigate_previous = Module.cwrap ('navigate_previous', 'void', ['string']);
		//console.log("prevQ called");
		my_log ("navigate_previous: " +  navigate_previous);
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
		if($("#selectGPS").val()=="on" && !(global_survey_related_info.position))
		{
			alert("Cannot proceed without GPS");
		}
		//global_survey_related_info.position && global_survey_related_info.position.coords &&
		else if (
			test_numeric_serial &&
			global_survey_related_info.device && global_survey_related_info.device.uuid &&
			global_survey_related_info.fileSystemObject)  {
			question_view.style.display = "block";
			var div_serial_no = document.getElementById("div_serial_no");
			div_serial_no.style.display = "none";
			return_serial_no_button.disabled = true;
			//my_log ("sanity checks passed");

			var our_dir_path = "qscript/" +
					global_survey_related_info.device.uuid + "/" +
					global_survey_related_info.job_name +  "/interviewer_id/incomplete";
			MakePathDir (our_dir_path);
			var our_path =  our_dir_path +
					//"qscript/" +
					//global_survey_related_info.device.uuid +
					//global_survey_related_info.job_name + interviewer_id + "/incomplete/" +
					"/" + global_survey_related_info.job_name + "_interviewer_id_" +
					serial_no + ".dat";
			var our_gps_path = our_dir_path +
						//"qscript/" +
						//global_survey_related_info.device.uuid +
						//"/project_name/interviewer_id/completed/vegetable_interviewer_id_" +
						"/" + serial_no + ".gps";				
			//alert ("our_path:" + our_path);
			// first try to open the file and see if it exists
			//my_log("opening file:" + our_path);
			global_survey_related_info.serial_no = serial_no;
			global_survey_related_info.our_dir_path = our_dir_path;
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
		/*
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
			document.getElementById("newNextQDiv").style.display = "block";	// enable next button
		} else {
			my_log ("Could not find callback_return_serial in Module.cwrap");
		}
		*/
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
			alert ("Please enter a valid serial no" );
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

	function create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr, question_text_obj_arr) {
		my_log ("Enter create_multiple_questions_view:" + 
				"questions_obj_arr.length: " + questions_obj_arr.length + 
				"question_text_obj_arr[0].question_text_arr.length: " + question_text_obj_arr[0].question_text_arr.length 
				);
		//my_log ("question_text_obj_arr.question_text_arr[0]: " + question_text_obj_arr.question_text_arr[0]);
		if (question_text_obj_arr) {
			my_log ("question_text_obj_arr exists");
			//if (question_text_obj_arr.question_text_arr) {
			//	my_log ("question_text_obj_arr.question_text_arr exists");
			//	my_log ("question_text_obj_arr.question_text_arr[0]: " + question_text_obj_arr.question_text_arr[0]);
			//}
		}
		//if (questions_obj_arr[0].question_type == 'nqq')
		if (questions_obj_arr[0].question_type == "nqq") {
			my_log ("case nqq");
			var new_question_view = "";

			for (var i=0; i<questions_obj_arr.length; i++) {
				var curr_question_obj = questions_obj_arr[i];
				new_question_view += "<p> nxd " + curr_question_obj.question_text_arr[0] + "</p>";
				if (global_survey_related_info.qnre_lang_obj) {
					my_log ("deferencing hindi translation array");
					new_question_view += "<p>" + global_survey_related_info.qnre_lang_obj[
						global_survey_related_info.current_language ] .  question_text_obj_arr.question_text_arr[0]  + "</p>";
				} else {
					my_log ("global_survey_related_info does not have qnre_hi_obj");
				}
				// dreference json language array text translations with Key from below here
				//new_question_view += "<p>" + question_text_obj_arr.question_text_arr[0] + "</p>";
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
					new_question_view += "comparing: " + questions_obj_arr[i].question_text_arr[0] + "," + questions_obj_arr[0].question_text_arr[0];
					if (questions_obj_arr[i].question_text_arr[0] != questions_obj_arr[0].question_text_arr[0]) {
						is_question_text_same = false;
						break;
					}
				}


				/*
				if (global_survey_related_info.qnre_hi_obj) {
					my_log ("deferencing hindi translation array question_text_obj_arr.length :" + question_text_obj_arr.question_text_arr.length);
					var translated_text = "";
					//question_title_div.innerHTML += "<p>nxd:" + global_survey_related_info.qnre_hi_obj[
					//	question_text_obj_arr.question_text_arr[0] ] + "</p>";
					for (var t1=0; t1 < question_text_obj_arr.question_text_arr.length; ++t1) {
						if (question_text_obj_arr.question_text_arr[t1].texpr_type === "simple_text") {
							translated_text += qnre_hi_obj[question_text_obj_arr.question_text_arr[t1].key[0]];
						}
						if (question_text_obj_arr.question_text_arr[t1].texpr_type === "named_attr") {
							translated_text += qnre_hi_obj[question_text_obj_arr.question_text_arr[t1].key[0]];
						}
						if (question_text_obj_arr.question_text_arr[t1].texpr_type === "nq") {
							translated_text += qnre_hi_stubs_obj[question_text_obj_arr.question_text_arr[t1].key[0]];
						}
					}
					question_title_div.innerHTML += "<p>nxd:" + translated_text + "</p>";
				} else {
					my_log ("global_survey_related_info does not have qnre_hi_obj");
				}
				*/
				
				new_question_view = "<p> is_question_text_same : " + is_question_text_same +  " </p><table>";
				if (is_question_text_same) {
					var translated_text = "";
					new_question_view += "<tr><th>" + questions_obj_arr[0].question_text_arr[0];
					var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
					var key =  question_text_obj_arr[0].question_text_arr[0].key[0];
					if (question_text_obj_arr[0].question_text_arr[0].texpr_type === "simple_text") {
						//translated_text += qnre_hi_obj[question_text_obj_arr[0].question_text_arr[0].key[0]];
						translated_text += language_translation_obj[key];
					}
					new_question_view += "<b>" + translated_text + "</b>" + "</th></tr>";
				}

				var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
				for (var i=0; i<questions_obj_arr.length; i++) {
					var curr_question_obj = questions_obj_arr[i];
					if (!is_question_text_same) {
						new_question_view += "<tr><td>hello-1" + curr_question_obj.question_text_arr[0] + "</td></tr>";
					}
					new_question_view += "<tr><td>:" + curr_question_obj.question_text_arr[1];
					//new_question_view += "len: " + question_text_obj_arr[i].question_text_arr.length;
					for (var j=1; j < question_text_obj_arr[i].question_text_arr.length; ++j) {
						//new_question_view += "/" + qnre_hi_stubs_obj[question_text_obj_arr[i].question_text_arr[j].key[0]];
						var key =  question_text_obj_arr[i].question_text_arr[j].key[0];
						new_question_view += "/" + language_translation_obj[key];
					}
					new_question_view += "</td>";
					new_question_view += "<td><form id ='id_form_" + curr_question_obj.qno + "' name ='form_" + curr_question_obj.qno + "' >";			
					new_question_view += "<input cols='40' rows='8' type='number' id='input_" + curr_question_obj.qno + "' name='input_" + curr_question_obj.qno + "'></input>";
					new_question_view += "</form></td></tr>";
				}
				new_question_view += "</table>";

			}


			if (err_obj_arr[0]) {
				new_question_view +=  "<p style='color:red;'>" + err_obj_arr.join("</p><p style='color:red;'>") + "</p>";
			}

			document.getElementById("new_question_view").innerHTML = new_question_view;	


			if (questions_obj_arr[0].no_mpn > 1) {

				var verbatim_response_path = "qscript/" +
				global_survey_related_info.device.uuid +
				"/" + global_survey_related_info.job_name + "/interviewer_id/incomplete/" +
				//global_survey_related_info.questionName_ +
				//"q1_1" +
				questions_obj_arr[0].qno +
				"." + global_survey_related_info.job_name + " _interviewer_id_" +
				global_survey_related_info.serial_no +
				".dat";
				//alert(verbatim_response_path);
				//alert(fileGetDir);
				if (fileGetDir) {

				}

				/*
				my_log ("Creating the verbatim data file handle");
				fileGetDir (verbatim_response_path, save_verbatim_data_file_handle,
				{create: true, exclusive: false},
				getFileErrorHandler,
				{create_verbatim_handler: true});
				my_log ("Finished Creating the verbatim data file handle");
				*/
			global_survey_related_info.fileSystemObject.root.getFile(
				verbatim_response_path, {create: true}, gotVerbatimFileEntry, getFileErrorHandler);
			}
		} else if (questions_obj_arr[0].question_type == 'video_q') {
			my_log ("Enter video_q section media_url:" + questions_obj_arr[0].media_url);
			var new_html =
				"<div>This is a video Question</div>" +
				"<div>" +
				"<video src=\"" + questions_obj_arr[0].media_url + "\" width=\"300\" height=\"200\" id=\"myVideo\">Video player not available.</video>" +
				"</div>";
			var new_question_view = document.getElementById("new_question_view");
			new_question_view.innerHTML = new_html;
		} else if (questions_obj_arr[0].question_type == 'video_capture') {
			var media_capture_file_path = "qscript/" +
				global_survey_related_info.device.uuid +
				"/" + global_survey_related_info.job_name + "/interviewer_id/incomplete/" +
				//global_survey_related_info.questionName_ +
				//"q1_1" +
				questions_obj_arr[0].qno +
				"." + global_survey_related_info.job_name + " _interviewer_id_" +
				global_survey_related_info.serial_no +
				".dat";
			global_survey_related_info.fileSystemObject.root.getFile(
						media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
			var new_html = "<button onclick=\"captureVideo();\">Capture Video</button> <br>"+
			    			"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>";
			var new_question_view = document.getElementById("new_question_view");
			new_question_view.innerHTML = new_html;
		} else if (questions_obj_arr[0].question_type == 'image_capture') {
			var media_capture_file_path = "qscript/" +
				global_survey_related_info.device.uuid +
				"/" + global_survey_related_info.job_name + "/interviewer_id/incomplete/" +
				//global_survey_related_info.questionName_ +
				//"q1_1" +
				questions_obj_arr[0].qno +
				"." + global_survey_related_info.job_name + " _interviewer_id_" +
				global_survey_related_info.serial_no +
				".dat";
			global_survey_related_info.fileSystemObject.root.getFile(
						media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
			var new_html = "<button onclick=\"capturePhoto();\">Capture Photo</button> <br>" + 
			    			"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>"
			var new_question_view = document.getElementById("new_question_view");
			new_question_view.innerHTML = new_html;
		} else if (questions_obj_arr[0].question_type == 'audio_capture') {
			var media_capture_file_path = "qscript/" +
				global_survey_related_info.device.uuid +
				"/" + global_survey_related_info.job_name + "/interviewer_id/incomplete/" +
				//global_survey_related_info.questionName_ +
				//"q1_1" +
				questions_obj_arr[0].qno +
				"." + global_survey_related_info.job_name + " _interviewer_id_" +
				global_survey_related_info.serial_no +
				".dat";
			global_survey_related_info.fileSystemObject.root.getFile(
						media_capture_file_path, {create: true}, gotMediaFileEntry, getFileErrorHandler);
			var new_html = "<button onclick=\"captureAudio();\">Capture Audio</button> <br>" +
			    			"<img style='display:none;width:60px;height:60px;' id='smallImage' src='' /><br>"

		} else {
			my_log ("case else ");

			/*
			var dummy_question_title_data = "{" + 
			    "\"q_text_arr\": [" + 
				"{" +
				    "\"texpr_type\": \"simple_text\"," + 
				    "\"key\": [" +
					"\"q3_0\"" +
				    "]" + 
				"}," +
				"{" +
				    "\"texpr_type\": \"named_attr\"," +
				    "\"key\": [" +
					"\"veg_seg_att_0\"" +
				    "]" + 
				"}," + 
				"{" +
				    "\"texpr_type\": \"nq\"," +
				    "\"key\": [" +
					"\"veg_4\"" + 
				    "]" +
				"}" +
			    "]" +
			"}";
			try { 
				dummy_question_title_obj = JSON.parse(dummy_question_title_data);
			} catch (error) {
				my_log ("unable to parse dummy_question_title_data" + error.message);
			}

			my_log ("dummy_question_title_data: " + dummy_question_title_data);
			my_log ("dummy_question_title_obj.q_text_arr.length: " + dummy_question_title_obj.q_text_arr.length);
			*/
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

				//if (global_survey_related_info.qnre_hi_obj) {
					//my_log ("deferencing hindi translation array question_text_obj_arr.length :" + question_text_obj_arr.length );
					//my_log ("deferencing hindi translation array question_text_obj_arr.length :" + question_text_obj_arr.question_text_arr.length);
					var translated_text = "";
					////question_title_div.innerHTML += "<p>nxd:" + global_survey_related_info.qnre_hi_obj[
					////	question_text_obj_arr.question_text_arr[0] ] + "</p>";
					//var question_text_arr = question_text_obj_arr[i].question_text_arr;
					for (var t1=0; t1 < question_text_obj_arr[i].question_text_arr.length; ++t1) {
						var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
						var key =  question_text_obj_arr[i].question_text_arr[t1].key[0];
						if (question_text_obj_arr[i].question_text_arr[t1].texpr_type === "simple_text") {
							//translated_text += qnre_hi_obj[question_text_obj_arr[i].question_text_arr[t1].key[0]];
							//translated_text += qnre_lang_obj[global_survey_related_info.current_language].question_text_obj_arr[i].question_text_arr[t1].key[0];
							//alert (qnre_lang_obj["hi"].q4_0);
							//if (qnre_lang_obj.hi) {
							//	translated_text += "qnre_lang_obj has hi: ";
							//}
							//alert ("v2:" + v2);
							//alert (v2.q4_0);
							//alert ("deref key in v2: " +  v2[key]);
							//var v1 = qnre_lang_obj[global_survey_related_info.current_language];
							//my_log ("v1: " + v1);
							//translated_text += "current_language: " + global_survey_related_info.current_language;
							//translated_text += "nxd: " + v1;
							//translated_text += "key: " + question_text_obj_arr[i].question_text_arr[t1].key[0];
							//translated_text +=  v1["q4_0"];
							//if (v1.q4_0) {
							//	translated_text += "has q4_0" ;
							//} else {
							//	translated_text += "DOES NOT have q4_0";
							//}
							//if (v1.q5_0) {
							//	translated_text += "has q5_0";
							//} else {
							//	translated_text += "DOES NOT have q5_0";
							//}
							//if (v1.q6_0) {
							//	translated_text += "has q6_0";
							//} else {
							//	translated_text += "DOES NOT have q6_0";
							//}
							translated_text += language_translation_obj[key];
						}
						if (question_text_obj_arr[i].question_text_arr[t1].texpr_type === "named_attr") {
							//translated_text += qnre_hi_obj[question_text_obj_arr[i].question_text_arr[t1].key[0]];
							translated_text += language_translation_obj[key];
						}
						if (question_text_obj_arr[i].question_text_arr[t1].texpr_type === "nq") {
							//translated_text += qnre_hi_stubs_obj[question_text_obj_arr[i].question_text_arr[t1].key[0]];
							translated_text += language_translation_obj[key];
						}
					}
					question_title_div.innerHTML += "<p>nxd:" + translated_text + "</p>";
				//} else {
				//	my_log ("global_survey_related_info does not have qnre_hi_obj");
				//}


				/*
				var dummy_question_title = "";
				for (var j = 0; j < dummy_question_title_obj.q_text_arr.length; ++j) {
					dummy_question_title += "dummy_question_title_obj.q_text_arr[j].texpr_type : " +
							dummy_question_title_obj.q_text_arr[j].texpr_type + "<br />";
					if (dummy_question_title_obj.q_text_arr[j].texpr_type === "simple_text") {
						dummy_question_title += "simple_text: " + qnre_hi_obj[dummy_question_title_obj.q_text_arr[j].key[0]];
					} 

					if (dummy_question_title_obj.q_text_arr[j].texpr_type === "named_attr") {
						dummy_question_title += "n_attr: " + qnre_hi_obj[dummy_question_title_obj.q_text_arr[j].key[0]];
					}

					if (dummy_question_title_obj.q_text_arr[j].texpr_type === "nq") {
						dummy_question_title += "nq: " + qnre_hi_stubs_obj[dummy_question_title_obj.q_text_arr[j].key[0]];
					}
				}
				question_title_div.innerHTML += dummy_question_title;
				*/


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
				//my_log ("after create a_question_div" );
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
	}

	function create_grid_questions_view (questions_obj_arr, stubs_obj_arr) {
		/*my_log ("Enter: create_grid_questions_view" );
		var new_question_view = document.getElementById("new_question_view");
		new_question_view.innerHTML = "<p>" + "from ui_create_question_form with love" + "</p>";
		$( '#stubs_form_div' ).trigger( 'create' );
		my_log ("Exit: create_grid_questions_view"  );*/

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
					//my_log ("after setting input.value i = " + i);
					//var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
					var id_text = res2.name + res2.stubs[i].stub_code ;
					//alert("id_text: " + id_text);
					input.id  = id_text;
					//alert ("id_text:" + id_text);
					var input_label   = document.createElement("label");
					//input_label.innerHTML = res2.stubs[i].stub_text;
					//input_label.innerHTML = "<table><tr><td nowrap>" + res2.stubs[i].stub_text + "</td>";
					//input_label.innerHTML = "<table><tr><td>" + res2.stubs[i].stub_text + "</td>";
					//if (question_obj.stub_name === "yn") {
						var index;
						index = question_obj.stub_name + "_" + res2.stubs[i].stub_code;
						//my_log ("stub_name === yn : index: " + index);
						//input_label.innerHTML = "<table><tr><td>" + global_survey_related_info.qnre_hi_stubs_obj[index] + "</td>";
						var language_translation_obj = qnre_lang_obj[global_survey_related_info.current_language];
						//input_label.innerHTML = "<table><tr><td> index: " + index + ":deref:" + qnre_lang_obj[global_survey_related_info.current_language].index + "</td>";
						input_label.innerHTML = "<table><tr><td>";
						//input_label.innerHTML += " index: " + index + ":deref:" ;
						input_label.innerHTML += language_translation_obj[index];
						input_label.innerHTML += "</td>";
					//} else {
					//	input_label.innerHTML = "<table><tr><td>" + res2.stubs[i].stub_text + "</td>";
					//}
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

			/*
			//var stubs_form_div = document.getElementById("stubs_form_div");
			{
				var n_child_nodes = stubs_form_div.childNodes.length;
				//alert ( "stubs_form_div.childNodes.length: " + stubs_form_div.childNodes.length);
				//alert ("n_child_nodes:" + n_child_nodes);
				for (var i1 = n_child_nodes-1; i1 >= 0; --i1) {
					stubs_form_div.removeChild(stubs_form_div.childNodes[i1]);
				}
			}
			//alert("cleared all childNodes of stubs_form_div");
			*/
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


	function ui_create_question_form (questions_obj_arr, stubs_obj_arr, err_obj_arr, question_text_obj_arr) {
		//my_log ("Entered: ui_create_question_form questions_obj_arr:" + questions_obj_arr);
		my_log ("document.forms.length: " + document.forms.length);

		var result = analyse_page_structure (questions_obj_arr, stubs_obj_arr);
		if (result == "single_question") {
			my_log ("result == single_question");
			create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr, question_text_obj_arr);
		} else if (result == "multiple_questions_per_page") {
			create_multiple_questions_view (questions_obj_arr, stubs_obj_arr, err_obj_arr, question_text_obj_arr);
		} else if (result == "grid_question") {
			create_grid_questions_view (questions_obj_arr, stubs_obj_arr);
		} else {
			//my_log ("unhandled case - analyse_page_structure");
		}
		//my_log ("Exited: ui_create_question_form stubs_obj_arr:" + stubs_obj_arr);
	}


	function serialize (form, my_question_obj) {
		//my_log("Enter: serialize");
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
				//my_log ("case text");
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
						global_survey_related_info.current_verbatim_data = field.value;
						if (save_verbatim_data) {
							//my_log ("save_verbatim_data:" + save_verbatim_data);
						}
						if (fail_to_write_file) {
							//my_log ("fail_to_write_file:" + fail_to_write_file);
						}
						//my_log ("global_survey_related_info.verbatim_data_file_handle:" + global_survey_related_info.verbatim_data_file_handle);
						// old code
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
						global_survey_related_info.current_verbatim_data_file_fileEntry.createWriter (save_verbatim_data, fail_to_write_file);
					}
				}
			break;
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

		//my_log ("Enter: new_serialize: document.forms.length " +
		//		document.forms.length);
		var form_data_arr = [];
		var i = 0;
		for (i = 0; i < document.forms.length;  ++i) {
			var form_serialized_data = serialize (document.forms[i], global_survey_related_info.questions_obj_arr[i] );
			//console.log ("form_serialized_data:" );
			//my_log ("form_serialized_data:" + form_serialized_data);
			form_data_arr.push (form_serialized_data);
			//my_log ("form_data_arr: " + form_data_arr);
			//my_log ("finished loop iter i== " + i);
		}
		//my_log("Exit: new_serialize");
		return form_data_arr;
	}

	function sync() {
		if(window.navigator.onLine) {		// check for internet connection
			fnMoveFiles();
		}
		else {
			alert("Internet connection is not available.");
		}
	}

	function load_json() {
		//alert("jon loaded");
		$.ajax({ 
			url: 'index.json', 
			async: false,
			dataType: 'json',
			success: function(data) {
				document.getElementById("div_serial_no").getElementsByTagName("h3")[0].innerHTML = data.title;
				document.getElementById("div_serial_no").getElementsByTagName("h5")[0].innerHTML = data.description;
			}
		});
		
	}
	//load_json();
	document.addEventListener ("deviceready", load_json, false);

	//my_log ("Finished loading our_ui.js");

// file syn code start

function fnMoveFiles() {
    //get hold of the first file
    //window.resolveLocalFileSystemURI("file:///storage/emulated/0/qscript/789ce7b08da7bcfa/project_name/interviewer_id", onSuccessResolutionOfDir, onErrorResolutionOfDir);
    var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/readytosync";
    window.resolveLocalFileSystemURI(dirPath, onSuccessResolutionOfDir, onErrorResolutionOfDir);
    //move it
    //come back to this folder and try moving the next file
}

function onSuccessResolutionOfDir(de) {
    //alert(de.name);
    //alert(de.fullPath);
    var directoryReader = de.createReader();

    // Get a list of all the entries in the directory
    directoryReader.readEntries(onDirectoryReadSuccess, onDirectoryReadFail);

}

function onDirectoryReadFail(err) {
    alert("failed to read interviewer_id");
}

function onErrorResolutionOfDir(err) {
    alert("resolution failed");
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
	            params.dirpath = "/var/www/data/Demo/Vegetable/"+fnGetDeviceUUID()+"/inter1/synced";
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
    var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/readytosync";
    //var filePath = "file:///storage/emulated/0/qscript/789ce7b08da7bcfa/project_name/interviewer_id/" + r.response;
    var filePath = dirPath + "/" + JSON.parse(r.response).message.filename;
    //alert(filePath);
    window.resolveLocalFileSystemURI(filePath, onSuccessResolutionOfFileUpload, onTransferFail);

}

function onSuccessResolutionOfFileUpload(fe) {
	var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/synced";
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
    /*
    alert('Latitude: '    + position.coords.latitude          + '\n' +
    'Longitude: '         + position.coords.longitude         + '\n' +
    'Altitude: '          + position.coords.altitude          + '\n' +
    'Accuracy: '          + position.coords.accuracy          + '\n' +
    'Altitude Accuracy: ' + position.coords.altitudeAccuracy  + '\n' +
    'Heading: '           + position.coords.heading           + '\n' +
    'Speed: '             + position.coords.speed             + '\n' +
    'Timestamp: '         + position.timestamp                + '\n');
    */
    global_survey_related_info.position = position;

    //$("#btn_return_serial_no").removeAttr("disabled");
    $("#popupUndismissible").popup("close");

}

function fnGPSLocaterFailed(error)
{
	if(error.code!=2)
	{
	    alert('code: '    + error.code    + '\n' +'message: ' + error.message + '\n');
	    //$("#btn_return_serial_no").removeAttr("disabled");
	    $("#popupUndismissible").popup("close");
	    $("#selectGPS").val("off").slider("refresh");
	}
}
//gps code end

/*login code starts

function btnLogin() {
	//document.getElementsByTagName("body")[0].removeChild(document.getElementById("login_section"));
	//document.getElementsByTagName("body")[0].removeChild(document.getElementById("signup_section"));
	document.getElementById("login_section").style.display = "none";
	document.getElementById("div_serial_no").style.display = "block";

	document.getElementById("login_section").innerHTML = "";
	document.getElementById("signup_section").innerHTML = "";
}

function btnSignup() {
	document.getElementById("login_section").style.display = "none";
	document.getElementById("signup_section").style.display = "block";
}

function goToLogin() {
	document.getElementById("signup_section").style.display = "none";
	document.getElementById("login_section").style.display = "block";
}

// login code ends */

// this function will create required common directories
function createCommonDirectories() {
	var entryPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id";
	
	window.resolveLocalFileSystemURI(
		entryPath, 
		function(fileSystem) {
			fileSystem.getDirectory("readytosync", {create: true, exclusive: false}, null, null);
			fileSystem.getDirectory("synced", {create: true, exclusive: false}, null, null);
		}, 
		null
	);
}

// this will move completed surveys to readytosync folder
var moveToReadyToSync = {

	// resolve full directory path
	onGetDirectorySuccess: {
		init: function() {
			var entryPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/completed";
			window.resolveLocalFileSystemURI(entryPath, this.onSuccess, this.onError);
		},

		onSuccess: function(dir) {						
			moveToReadyToSync.onGetFileEntries.init(dir);
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
			moveToReadyToSync.onFileReaderSuccess.init(fileEntries);
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
						var dirPath = global_survey_related_info.fileSystemObject.root.fullPath + "/qscript/" + global_survey_related_info.device.uuid + "/project_name/interviewer_id/readytosync";
						var DirEntry = new DirectoryEntry("readytosync", dirPath);
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

function set_lang (the_lang) {
	my_log ("the_lang: " + the_lang);
	global_survey_related_info.current_language = the_lang;
}

	my_log ("Finished loading our_ui.js");
