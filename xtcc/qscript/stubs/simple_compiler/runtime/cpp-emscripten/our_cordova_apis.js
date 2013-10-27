
	my_log ("Started loading our_cordova_apis.js");


/* ==========  Device Info {{{1 ======================= */

	function get_device_info()
	{
		var div_has_PhoneGap = document.getElementById ("div_has_PhoneGap");
		if (div_has_PhoneGap) {
			div_has_PhoneGap.innerHTML = "PhoneGap library loaded successfully.";
		}
		var div_device_properties = document.getElementById ("div_device_properties");
		if (window.device) {
			///
			//div_device_properties.innerHTML =
			//	'Device Name: '     + device.name     + '<br />' +
			//	'Device Cordova: '  + device.cordova + '<br />' +
			//	'Device Platform: ' + device.platform + '<br />' +
			//	'Device UUID: '     + device.uuid     + '<br />' +
			//	'Device Model: '    + device.model     + '<br />' +
			//	'Device Version: '  + device.version  + '<br />';
			///
			//global_survey_related_info.device_name = device.name;
			//global_survey_related_info.device_cordova = device.cordova;
			//global_survey_related_info.device_platform = device.platform;
			//global_survey_related_info.device_uuid = device.uuid;
			//global_survey_related_info.device_model = device.model;
			//global_survey_related_info.device_version = device.version;
			global_survey_related_info.device = device;
			return true;
		} else {
			//div_device_properties.innerHTML = "does not have device property";
			// my_log ("DOES NOT HAVE DEVICE PROPERTY");
			return false;
		}
	}
	//my_log ("created get_device_info function");
/* ==========  End: Device Info }}}1 ======================= */
//
/* ==========  Compass API {{{1 ======================= */
	function onCompassSuccess(heading) {
		//alert('Heading: ' + heading.magneticHeading);
		var div_device_compass = document.getElementById("div_device_compass");
		//div_device_compass.innerHTML  = "compass heading: " + heading.magneticHeading;
	}
	function onCompassError(compassError) {
		//var div_device_compass = document.getElementById("div_device_compass");
		//div_device_compass.innerHTML  = "compass not available :" + compassError;
		//my_log ("does not have compass/compass not available");
	}

	function get_compass_info()
	{
		if (navigator.compass) {
			navigator.compass.getCurrentHeading(onCompassSuccess, onCompassError);
		} else {
			//var div_device_compass = document.getElementById("div_device_compass");
			//div_device_compass.innerHTML  = "does not have compass object";
			//my_log ("DOES NOT HAVE COMPASS OBJECT");
		}
	}
	//my_log ("created get_compass_info function");
/* ==========  End: Compass API }}}1 ======================= */

/* ==========  GeoLocation API {{{1 ======================= */
	function onGeoLocationSuccess (position) {
		//my_log ("Enter: onGeoLocationSuccess: position:" + position);
		var div_geolocation_info = document.getElementById("div_geolocation_info");
		if (div_geolocation_info == undefined)
		div_geolocation_info.innerHTML =
			'Latitude: '          + position.coords.latitude          + '<br/>' +
			'Longitude: '         + position.coords.longitude         + '<br/>' +
			'Altitude: '          + position.coords.altitude          + '<br/>' +
			'Accuracy: '          + position.coords.accuracy          + '<br/>' +
			'Altitude Accuracy: ' + position.coords.altitudeAccuracy  + '<br/>' +
			'Heading: '           + position.coords.heading           + '<br/>' +
			'Speed: '             + position.coords.speed             + '<br/>' +
			'Timestamp: '         + position.timestamp                + '<br/>';
		//global_survey_related_info.position.coords.latitude         =position.coords.latitude
		//global_survey_related_info.position.coords.longitude        =position.coords.longitude
		//global_survey_related_info.position.coords.altitude         =position.coords.altitude
		//global_survey_related_info.position.coords.accuracy         =position.coords.accuracy
		//global_survey_related_info.position.coords.altitudeAccuracy =position.coords.altitudeAccuracy
		//global_survey_related_info.position.coords.heading          =position.coords.heading
		//global_survey_related_info.position.coords.speed            =position.coords.speed
		//global_survey_related_info.position.timestamp               =position.timestamp
		global_survey_related_info.position = position;
	}
	//my_log("created onGeoLocationSuccess");

	// onError Callback receives a PositionError object
	//
	function onGeoLocationError(error) {
		//my_log ("Enter: onGeoLocationError");
		//var div_geolocation_info = document.getElementById("div_geolocation_info");
		//div_geolocation_info.innerHTML =
		//	'code: '    + error.code    + '<br/>' +
		//	'message: ' + error.message + '<br/>';
		//my_log ("Exit: onGeoLocationError");
		alert("GPS not available");
	}
	//my_log("created onGeoLocationError");

	function get_geolocation_info()
	{
		alert("get_geolocation_info fired");
		//my_log ("Enter: get_geolocation_info: navigator.geolocation:" + navigator.geolocation);
		if (navigator.geolocation) {
			// my_log ("get_geolocation_info: has geolocation");
			if (navigator.geolocation.getCurrentPosition) {
				// my_log("get_compass_info: has getCurrentPosition: " + navigator.geolocation.getCurrentPosition);
			}
			navigator.geolocation.getCurrentPosition(
				onGeoLocationSuccess, onGeoLocationError,{timeout:90000});
			return true;
		} else {
			var div_geolocation_info = document.getElementById("div_geolocation_info");
			div_geolocation_info.innerHTML += 'message: Does not have geolocation object' +  '<br/>';
			//my_log ("DOES NOT HAVE GEOLOCATION OBJECT");
			return false;
		}
		// my_log ("Exit: get_geolocation_info");
	}
	//my_log("created get_geolocation_info");
/* ==========  End: GeoLocation API }}}1 ======================= */


///* ==========  FileSystem API {{{1 ======================= */
	//my_log ("===========reached FileSystem section==========");

	//var fileSystemObject = null;
	// global Variable - current Active file
	//global_current_survey_data_file = null;

	//document.addEventListener("deviceready", getFileSystemObject, false);

	function onFileSystemSuccess (fileSystem) {
		//fileSystemObject = fileSystem;
		//my_log("assigned fileSystemObject fileSystem.name:" + fileSystem.name);
		//my_log("assigned fileSystemObject fileSystemObject.name:" +  fileSystem.name);
		//my_log("assigned fileSystemObject fileSystemObject.root.name:" +  fileSystem.root.name);
		//my_log("assigned fileSystemObject fileSystemObject.root.fullPath:" +  fileSystem.root.fullPath);
		//my_log("assigned fileSystemObject fileSystemObject.root.isDirectory:" +  fileSystem.root.isDirectory);
		global_survey_related_info.fileSystemObject = fileSystem;
	}

	function fileFSError(e) {
		//console.log(e.code);
		//try {
		//	my_log ("fileFSError: " + JSON.stringify(e));
		//} catch (err) {}
		//my_log ("=== ERROR ====  fileFSError: " + JSON.stringify(e));
	}

	function getFileSystemObject () {
		//my_log("Enter: getFileSystemObject");
		window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onFileSystemSuccess, fileFSError);
	}

/* ==========  End: FileSystem API }}}1 ======================= */

/* =============== File API {{{1 ==================== */

	function gotFile(file) {
		//my_log("Enter: gotFile");
		//readDataUrl(file);
		global_survey_related_info.current_survey_data_file = file;
		readAsText(file);
	}

	function gotGPSFile(file) {

	}
	

	/* getFileErrorHandler : {{{2 */
	function getFileErrorHandler (file_error) {
		/*var file_err_string =
			" file_error.NOT_FOUND_ERR              "   +  file_error.NOT_FOUND_ERR + "<br />" +
			" file_error.SECURITY_ERR               "   +  file_error.SECURITY_ERR + "<br />" +
			" file_error.ABORT_ERR                  "   +  file_error.ABORT_ERR + "<br />" +
			" file_error.NOT_READABLE_ERR           "   +  file_error.NOT_READABLE_ERR + "<br />" +
			" file_error.ENCODING_ERR               "   +  file_error.ENCODING_ERR + "<br />" +
			" file_error.NO_MODIFICATION_ALLOWED_ERR"   +  file_error.NO_MODIFICATION_ALLOWED_ERR + "<br />" +
			" file_error.INVALID_STATE_ERR          "   +  file_error.INVALID_STATE_ERR + "<br />" +
			" file_error.SYNTAX_ERR                 "   +  file_error.SYNTAX_ERR + "<br />" +
			" file_error.INVALID_MODIFICATION_ERR   "   +  file_error.INVALID_MODIFICATION_ERR + "<br />" +
			" file_error.QUOTA_EXCEEDED_ERR         "   +  file_error.QUOTA_EXCEEDED_ERR + "<br />" +
			" file_error.TYPE_MISMATCH_ERR          "   +  file_error.TYPE_MISMATCH_ERR + "<br />" +
			" file_error.PATH_EXISTS_ERR            "   +  file_error.PATH_EXISTS_ERR + "<br />"
			;*/
			//alert(file_error.code);
		var file_err_string = file_error.code;
		//my_log (file_err_string);
		//my_log ("triggering file_open_failed event");
		/*
		var event = new Event('file_open_failed');
		var span_event_target_trigger_file_open_write = document.getElementById("span_event_target_trigger_file_open_write");
		span_event_target_trigger_file_open_write.dispatchEvent (event);
		*/


		var span_event_target_trigger_file_open_write =
			document.getElementById("span_event_target_trigger_file_open_write");
		//my_log ("got span");
		var event = document.createEvent('HTMLEvents');
		//my_log ("created HTMLEvents");
		event.initEvent('click', true, true);
		//my_log ("did initEvent");
		span_event_target_trigger_file_open_write.dispatchEvent (event);
		//my_log ("triggered click event");
	}
	/* getFileErrorHandler }}}2 */

	function gotFileEntry(fileEntry) {
		my_log("Enter: gotFileEntry");
		global_survey_related_info.current_data_file_fileEntry = fileEntry;
		fileEntry.file(gotFile, getFileErrorHandler);
	}

	function gotGPSFileEntry(fileEntry) {		
		//alert("File Entry");
		fileEntry.createWriter(gotGPSFileWriter, getFileErrorHandler);
	}

	function gotGPSFileWriter(fw)
	{
		var timestamp = Math.round(+new Date()/1000);
		//alert(timestamp + ": writing GPS data");
		if(global_survey_related_info.position)
		{
			fw.seek(fw.length);
			fw.write("Lat:"+global_survey_related_info.position.coords.latitude+"&Long:"+global_survey_related_info.position.coords.longitude+"&Timestamp:"+timestamp+"\n");
		}
		else
		{
			fw.seek(fw.length);
			fw.write("Lat:NaN&Long:NaN&Timestamp:" + timestamp + "\n");
		}
	}
	

	/* readDataUrl {{{2 */
	function readDataUrl(file) {
		//my_log ("Enter: readDataUrl");
		var reader = new FileReader();
		reader.onloadend = function(evt) {
		    // my_log("Read as data URL");
		    //my_log(evt.target.result);
		};
		reader.readAsDataURL(file);
	}
	/* readDataUrl }}}2 */

	/* readAsText {{{2 */
	function readAsText(file) {
		//my_log ("Enter: readAsText");
		var reader = new FileReader();
		reader.onloadend = function(evt) {
			//my_log("Read as text:");
			//my_log(evt.target.result);
			var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
			if (evt.target.result.length > 0) {
				//my_log ("callback_return_serial:" + callback_return_serial);
				//if (callback_return_serial) {
				//	alert ("about to call callback_return_serial: global_survey_related_info.serial_no:" + global_survey_related_info.serial_no);
				//	callback_return_serial (global_survey_related_info.serial_no, evt.target.result);
				//} else {
				//	alert ("Not able to find function callback_return_serial");
				//}
				//if (global_survey_related_info.serial_no) {
				//	callback_return_serial (global_survey_related_info.serial_no, evt.target.result);
				//} else {
				//	alert ("serial_no not found on global_survey_related_info");
				//}
				if (callback_return_serial && global_survey_related_info.serial_no) {
					callback_return_serial (global_survey_related_info.serial_no, evt.target.result);
				} else {
					alert ("Error either callback_return_serial or global_survey_related_info.serial_no is null");
				}
			} else {
				my_log ("new data file");
				callback_return_serial (global_survey_related_info.serial_no, "");
			}
		};
		reader.readAsText(file);
	}
	/* readAsText }}}2 */

	function fail_to_write_file (err_msg) {
		//my_log (JSON.stringify(err_msg));
	};

	/* ourGotFileWriter {{{2  */
	function ourGotFileWriter (writer) {
		writer.write("This is some dummy verbatim data");
	}
	/* ourGotFileWriter }}}2 */

	/* save_verbatim_data{{{2 */
	function save_verbatim_data(writer) {
		//my_log ("Enter : save_verbatim_data");
		//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
		writer.write(global_survey_related_info.current_verbatim_data);
		//my_log ("Exit : save_verbatim_data");
	}
	/* save_verbatim_data }}}2 */

	/* save_verbatim_data_file_handle {{{2 */
	function save_verbatim_data_file_handle (fileEntry) {
		//my_log ("Enter : save_verbatim_data_file_handle");
		//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
		global_survey_related_info.verbatim_data_file_handle = fileEntry;
		//my_log ("Exit : save_verbatim_data_file_handle");
	}
	/* save_verbatim_data_file_handle }}}2 */

	/* fileFoundSuccess {{{2 */
	function fileFoundSuccess (file) {
		//my_log("Enter: fileFoundSuccess: file" + file);
		if (file) {
			//my_log ("file.size:" + file.size);
			//my_log ("file.fullPath:" + file.fullPath);
			//my_log ("file.name:" + file.name);
			//my_log ("file.type:" + file.type);
		}
		global_survey_related_info.file_entry_read_mode = file;
	}
	/* fileFoundSuccess }}}2 */

	/* ====== fileGetDir {{{2 */
	// http://stackoverflow.com/questions/13890698/how-to-create-nested-directories-in-phonegap
	// This function will create all the directories required on the way
	// but create_mode = false or true will decide if a new file will be created
	function fileGetDir(path, cb, create_mode, handlerFileDoesNotExist, function_mode) {
		//my_log ("Enter: fileGetDir, create_mode: " + create_mode + "create_mode.create: " + create_mode.create );
		my_log ("Enter: fileGetDir, create_mode: " + create_mode + "create_mode.create: " + create_mode.create +
			"function_mode: " +function_mode.toJSON());
		var fileCreatedSuccess_serno = function (file) {
			my_log ("Enter: fileCreatedSuccess_serno:" );
			//global_current_survey_data_file = file;
			global_survey_related_info.current_survey_data_file = file;
			var callback_return_serial = Module.cwrap ('callback_return_serial', 'void', ['int', 'string']);
			//my_log ("Exit: fileCreatedSuccess_serno:" );
			callback_return_serial (global_survey_related_info.serial_no, "");
		};
		var fileCreatedSuccess_verbatim = function (file) {
			//my_log ("Enter: fileCreatedSuccess_verbatim:" );
			//global_current_survey_data_file = file;
			global_survey_related_info.verbatim_data_file_handle = file;
			//my_log ("Exit: fileCreatedSuccess_verbatim:" );
		};
		var fnGetOrCreateDir = function(p, de) {
			//my_log ("fnGetOrCreateDir path:" + p);
			var path_length = p.length;
			var entry = p.shift();
			//my_log ("fnGetOrCreateDir operating on entry:" + entry);
			if (entry) {
				if (path_length > 1) {
					de.getDirectory(entry,
							{ create : true },
							function(dirEntry) {
								//my_log("success function: made dir/file: " + entry);
								fnGetOrCreateDir(p, dirEntry);
							},
							fileFSError);
				} else {
					if (create_mode.create == true) {
						//my_log("reached file creation: create = true");
						if (function_mode && function_mode.new_serial_no) {
							de.getFile(entry,
									{ create : true },
									fileCreatedSuccess_serno,
								fileFSError);
						} else if (function_mode && function_mode.create_verbatim_handler) {
							de.getFile(entry,
									{ create : true },
									fileCreatedSuccess_verbatim,
								fileFSError);
						}
					} else {
						//my_log("reached file creation: open for reading only = true");
						de.getFile(entry,
								{ create : false },
								fileFoundSuccess,
							handlerFileDoesNotExist);
					}
				}
			} else if (cb) {
				cb(de);
			}
		};
		//my_log ("After: fileGetDir");
		/*
		var callback_function = null;
		if (function_mode.create_verbatim_handler && function_mode.create_verbatim_handler == true) {
			callback_function = fileCreatedSuccess_verbatim;
			//my_log ("callback_function: fileCreatedSuccess_verbatim:" + callback_function);
		} else if (function_mode.new_serial_no && function_mode.new_serial_no == true) {
			callback_function = fileCreatedSuccess_serno;
			//my_log ("callback_function: fileCreatedSuccess_serno:" + callback_function);
		} else {
			//my_log ("fileGetDir: function_mode - unhandled ");
			return;
		}
		*/
		if (path) {
			var arPath = path.split("/");
			fnGetOrCreateDir(arPath,
					global_survey_related_info.fileSystemObject.root);
		} else {
			if (cb) cb(global_survey_related_info.fileSystemObject.root);
		}
		/*
		*/
		//my_log ("Exit: fileGetDir " + create_mode);
	}
	//my_log("created fileGetDir");
	/* ====== fileGetDir }}}2 */

	function printSuccess(dirEntry) {
		//my_log("printSuccess: " + dirEntry.fullPath);
	}
/* =============== End: File API }}}1 ==================== */


	/* ============ Setup the UI {{{1 ==================== */


	var testReadFile = document.getElementById ("testReadFile");
	EventUtil.addHandler (testReadFile, "click", function(event) {
		global_survey_related_info.fileSystemObject.root.getFile("qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat", null, gotFileEntry, getFileErrorHandler);
	});
	//my_log ("created submit handler function");

/* test_file_read_failure {{{2 */
var test_file_read_failure = document.getElementById("test_file_read_failure");
function test_file_read_failure_handler ()
{
	//my_log ("Enter: test_file_read_failure_handler");
	var our_path = "qscript/" +
					global_survey_related_info.device.uuid +
					"/project_name/interviewer_id/project_name_interviewer_id_does_not_exist.dat";
					//serial_no +
					//".dat"
					//;
	//my_log ("our_path:" + our_path);
	// first try to open the file and see if it exists
	//my_log("opening file:" + our_path);
	global_survey_related_info.fileSystemObject.root.getFile(
		our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
}
EventUtil.addHandler (test_file_read_failure, "click", test_file_read_failure_handler);
/* test_file_read_failure }}}2 */


/* test_file_read_failure_middle_dir_missing: {{{2 */
var test_file_read_failure_middle_dir_missing = document.getElementById("test_file_read_failure_middle_dir_missing");
function test_file_read_failure_middle_dir_missing_handler ()
{
	//my_log ("Enter: test_file_read_failure_middle_dir_missing_handler");
	var our_path = "qscript/" +
			global_survey_related_info.device.uuid +
			"/project_name_missing/interviewer_id/project_name_interviewer_id_does_not_exist.dat";
	//my_log ("our_path:" + our_path);
	// first try to open the file and see if it exists
	//my_log("opening file:" + our_path);
	global_survey_related_info.fileSystemObject.root.getFile(
		our_path, {create: false, exclusive: true}, gotFileEntry, getFileErrorHandler);
}
	EventUtil.addHandler (test_file_read_failure_middle_dir_missing,
		"click", test_file_read_failure_middle_dir_missing_handler);
/* test_file_read_failure_middle_dir_missing: }}}2 */

	var span_event_target_trigger_file_open_write =
			document.getElementById("span_event_target_trigger_file_open_write");
function event_listener_failed_read_open (e)
{
	//my_log ("Enter: event_listener_failed_read_open: open_file_path: " + global_survey_related_info.open_file_path);
	fileGetDir (global_survey_related_info.open_file_path, printSuccess,
		    {create: true, exclusive: true},
		    getFileErrorHandler,
		    {new_serial_no: true});
	//my_log ("exit: event_listener_failed_read_open: open_file_path: " + global_survey_related_info.open_file_path);
}

	EventUtil.addHandler (span_event_target_trigger_file_open_write,
		"click", event_listener_failed_read_open);
	/* ============ Setup the UI }}}1 ==================== */


function toggle_options_panel() {
	$("#options-panel").panel("toggle");
}
// implment back button
document.addEventListener("backbutton", function() {
	if( $('#newNextQDiv').css('display') == "block") {
		$('#prevQ').click();
	}
	else if( $('#login_section').css('display') == 'block') {
		$('#welcome_section').show();
		$('#login_section').hide();
	}
	else if( $('#signup_section').css('display') == 'block') {
		$('#welcome_section').show();
		$('#signup_section').hide();
	}
}, false);

// implment menu button
document.addEventListener("menubutton", toggle_options_panel, false);

//function onDeviceReady() {
//	my_log("Enter onDeviceReady");
//	var success = false;
//	success = get_device_info();
//	if (success == false) {
//		//my_log ("Unable to get device information ... exiting the survey");
//		return false;
//	}
//	/*
//	success = get_compass_info();
//	if (success == false) {
//		//my_log ("Unable to get compass information ... exiting the survey");
//		return false;
//	}*/
//	success = get_geolocation_info();
//	if (success == false) {
//		//my_log ("Unable to get geolocation information ... exiting the survey");
//		return false;
//	}
//	
//	getFileSystemObject();
//	//if (success == false) {
//	//	//my_log ("Unable to get LocalFileSystem ... exiting the survey");
//	//	return false;
//	//}
//	// allow to click on start only after initializing all the things we need
//	var return_serial_no_button = document.getElementById("btn_return_serial_no");
//	return_serial_no_button.disabled = false;
//	my_log("ready to start interview");
//	// var our_path = "qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat";
//	// fileGetDir (our_path, printSuccess);
//	//
//	//
//	//
//	//
//	//
//	//if(fnVerifyCurrentUserInLocalStorage())
//	//{
//	//	//$.mobile.changePage( "#pageSurveys", { transition: "slideup"});
//	//	showSurveys();
//	//}
//	my_log ("Exit onDeviceReady");
//	return true;
//}
//document.addEventListener ("deviceready", onDeviceReady, false);

	my_log ("Finished loading our_cordova_apis.js");
