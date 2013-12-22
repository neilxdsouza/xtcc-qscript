
//my_log ("Started loading our_cordova_apis.js");


/* ==========  Device Info {{{1 ======================= */

function get_device_info()
{
	var div_has_PhoneGap = document.getElementById ("div_has_PhoneGap");
	if (div_has_PhoneGap) {
		div_has_PhoneGap.innerHTML = "PhoneGap library loaded successfully.";
	}
	var div_device_properties = document.getElementById ("div_device_properties");
	if (window.device) {
		global_survey_related_info.device = device;
		return true;
	} else {
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
	
	/*alert("GPS not available");*/
}
//my_log("created onGeoLocationError");

function get_geolocation_info()
{
	//alert("get_geolocation_info fired");
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
		div_geolocation_info.innerHTML += 'message: Does not have geolocation object' + '<br/>';
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
//
//
function onResolveError(evt) {
	my_log ( "onResolveError: filesystem entry uri failed to resolve");
}

function onFileSystemSuccess (fileSystem) {
	global_survey_related_info.fileSystemObject = fileSystem;
	my_log ("global_survey_related_info.fileSystemObject.root.name: " +  global_survey_related_info.fileSystemObject.root.name);
	my_log ("global_survey_related_info.fileSystemObject.name: " +  global_survey_related_info.fileSystemObject.name);

	window.resolveLocalFileSystemURI("file:///sdcard/our_ui.js", onResolveSuccess, onResolveError);
}


function onResolveSuccess(fileEntry) {
	my_log("onResolveSuccess: " + fileEntry.name);
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
	my_log ("getFileErrorHandler: unable to open requested file");	
	var file_err_string = file_error.code;
	//my_log (file_err_string);
	//my_log ("triggering file_open_failed event");
}
/* getFileErrorHandler }}}2 */

function gotFileEntry(fileEntry) {
	//my_log("Enter: gotFileEntry");
	global_survey_related_info.current_data_file_fileEntry = fileEntry;
	fileEntry.file(gotFile, getFileErrorHandler);
}
/*
function gotVerbatimFile(file) {
	var reader = new FileReader();
	reader.onloadend = function(evt) {
		my_log ("Read verbatim data: " + evt.target.result);
		my_log ("global_survey_related_info.current_verbatim_index: " + global_survey_related_info.current_verbatim_index);
		var verb_text_box = document.getElementById( global_survey_related_info.verbatim_text_box_id_arr[
				global_survey_related_info.current_verbatim_index]);
		if (verb_text_box) {
			verb_text_box.value = evt.target.result;
		}
	//	console.log(evt.target.result);
	};
	reader.readAsText(file);
}

function gotVerbatimFileEntry(fileEntry) {
	my_log("Enter: gotVerbatimFileEntry");
	if (global_survey_related_info.verbatim_data_file_fileEntry_arr === undefined) {
		global_survey_related_info.verbatim_data_file_fileEntry_arr  = [];
	}
	//global_survey_related_info.current_verbatim_data_file_fileEntry = fileEntry;
	global_survey_related_info.verbatim_data_file_fileEntry_arr.push(fileEntry);
	fileEntry.file(gotVerbatimFile, getFileErrorHandler);
}
*/

	function gotOtherSpecifyFileEntry(fileEntry) {
		my_log("Enter: gotOtherSpecifyFileEntry");
		//global_survey_related_info.current_verbatim_data_file_fileEntry = fileEntry;
		if (global_survey_related_info.other_specify_data_file_fileEntry_arr === undefined) {
			global_survey_related_info.other_specify_data_file_fileEntry_arr = [];
		}
		global_survey_related_info.other_specify_data_file_fileEntry_arr.push(fileEntry); 
	}

	function gotMediaFileEntry(fileEntry) {
		my_log("Enter: gotMediaFileEntry");
		if (global_survey_related_info.media_fileEntry_arr === undefined) {
			global_survey_related_info.media_fileEntry_arr = [];
		}
		//global_survey_related_info.current_media_capture_file_fileEntry = fileEntry;
		global_survey_related_info.media_fileEntry_arr.push(fileEntry);
	}

	function gotGeocodeFileEntry(fileEntry) {
		my_log("Enter: gotGeocodeFileEntry");
		if (global_survey_related_info.geocode_fileEntry_arr === undefined) {
			global_survey_related_info.geocode_fileEntry_arr = [];
		}
		//global_survey_related_info.current_media_capture_file_fileEntry = fileEntry;
		global_survey_related_info.geocode_fileEntry_arr.push(fileEntry);
	}

	function gotAddressFileEntry(fileEntry) {
		my_log("Enter: gotAddressFileEntry");
		if (global_survey_related_info.address_fileEntry_arr === undefined) {
			global_survey_related_info.address_fileEntry_arr = [];
		}
		//global_survey_related_info.current_media_capture_file_fileEntry = fileEntry;
		global_survey_related_info.address_fileEntry_arr.push(fileEntry);
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
		fw.write(global_survey_related_info.position.coords.latitude+","+global_survey_related_info.position.coords.longitude+","+timestamp+"\n");
	}
	else
	{
		fw.seek(fw.length);
		fw.write("NaN,NaN," + timestamp + "\n");
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
	my_log ("Enter : save_verbatim_data: global_survey_related_info.current_verbatim_index: " + global_survey_related_info.current_verbatim_index);
	//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
	//writer.write(global_survey_related_info.current_verbatim_data);
	//writer.write(global_survey_related_info.current_verbatim_data);
	writer.write(global_survey_related_info.verbatim_data_arr[global_survey_related_info.current_verbatim_index]);
	my_log ("Exit : save_verbatim_data");
}
/* save_verbatim_data }}}2 */

/* save_geocode_data{{{2 */
function save_geocode_data(writer) {
	my_log ("Enter : save_geocode_data: " );
	//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
	//writer.write(global_survey_related_info.current_geocode_data);
	//writer.write(global_survey_related_info.current_geocode_data);
	writer.write(global_survey_related_info.geocode_question_data[global_survey_related_info.current_geocode_question]);
	my_log ("Exit : save_geocode_data");
}
/* save_geocode_data }}}2 */

/* save_address_data{{{2 */
function save_address_data(writer) {
	my_log ("Enter : save_address_data: " );
	//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
	//writer.write(global_survey_related_info.current_address_data);
	//writer.write(global_survey_related_info.current_address_data);
	writer.write(global_survey_related_info.geocode_addr_data_json);
	my_log ("Exit : save_address_data");
}
/* save_address_data }}}2 */

/* save_verbatim_data_file_handle {{{2 */
function save_verbatim_data_file_handle (fileEntry) {
	//my_log ("Enter : save_verbatim_data_file_handle");
	//fileEntry.createWriter (ourGotFileWriter, fail_to_write_file);
	global_survey_related_info.verbatim_data_file_handle = fileEntry;
	//my_log ("Exit : save_verbatim_data_file_handle");
}
/* save_verbatim_data_file_handle }}}2 */


	/* save_media_data{{{2 */
	function save_media_path_data(writer) {
		my_log ("Enter : save_media_data");
		writer.write(global_survey_related_info.media_path_data);
		my_log ("Exit : save_media_data");
	}
	/* save_media_data }}}2 */

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

function MakePathDir(path) {
	my_log ("MakePathDir path: " + path);
	var path_array = path.split("/");
	var i = 0;
	var root_dir_entry = global_survey_related_info.fileSystemObject.root;
	//var current_dir_entry = root_dir_entry;
	//var next_dir_entry = current_dir_entry;
	//var path_array_copy = path_array;
	var cumulative_path = "";
	var dir_created_success = function (p, de) {
					};
	// for (; i < path_array.length; ++i) {
	// 	my_log ("cumulative_path: " + cumulative_path);
	// 	cumulative_path += "/" + path_array[i];
	// 	root_dir_entry.getDirectory (cumulative_path, { create: true },
	// 							dir_created_success,
	// 							fileFSError);
	// }
	var fnGetOrCreateDir2 = function(p, de) {
		//my_log ("fnGetOrCreateDir2 path:" + p);
		var path_length = p.length;
		var entry = p.shift();
		//my_log ("fnGetOrCreateDir2 operating on entry:" + entry);
		if (entry) {
			if (path_length > 0) {
				de.getDirectory(entry,
						{ create : true },
						function(dirEntry) {
							//my_log("success function: made dir/file: " + entry);
							fnGetOrCreateDir2(p, dirEntry);
						},
						fileFSError);
			} else {
			}
		}
	}
	fnGetOrCreateDir2 (path_array, global_survey_related_info.fileSystemObject.root);
}

/* ====== fileGetDir {{{2 */
// http://stackoverflow.com/questions/13890698/how-to-create-nested-directories-in-phonegap
// This function will create all the directories required on the way
// but create_mode = false or true will decide if a new file will be created
function fileGetDir(path, cb, create_mode, handlerFileDoesNotExist, function_mode) {
	//my_log ("Enter: fileGetDir, create_mode: " + create_mode + "create_mode.create: " + create_mode.create );
	//my_log ("Enter: fileGetDir, create_mode: " + create_mode + "create_mode.create: " + create_mode.create +
	//	"function_mode: " +function_mode.toJSON());
	var fileCreatedSuccess_serno = function (file) {
		//my_log ("Enter: fileCreatedSuccess_serno:" );
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

// implment menu button
document.addEventListener("menubutton", toggle_options_panel, false);

my_log ("Finished loading our_cordova_apis.js");

function capturePhoto() 
{
	my_log ("enter capturePhoto");
	if (navigator.device.capture) {
		my_log ("has navigator.device.capture");
		navigator.device.capture.captureImage(FileCaptureSuccess, onFail, null);
	} else {
		my_log ("not capture available");
	}
	my_log ("exit capturePhoto");
}


function capturePhoto2(index) 
{
	my_log ("enter capturePhoto2, index: " + index);
	if (global_survey_related_info.media_path_data_arr === undefined) {
		global_survey_related_info.media_path_data_arr = [];
	}

	var save_media_path_data2 = function (writer) {
		my_log ("Enter : save_media_path_data2");
		writer.write(global_survey_related_info.media_path_data_arr[index]);
		my_log ("Exit : save_media_path_data2");
	};

	var CaptureSuccess = function (mediaFiles) {
		my_log ("enter CaptureSuccess");
		var media_file_paths = "", i=0, len = 0;
		for (i = 0, len = mediaFiles.length; i < len; i += 1) {
			//window.resolveLocalFileSystemURI(mediaFiles[i].fullPath, moveFile, onFail);
			my_log ("filename captured: " + mediaFiles[i].fullPath);
			media_file_paths += mediaFiles[i].fullPath + '\n';
			window.resolveLocalFileSystemURI(mediaFiles[i].fullPath, moveFile, onFail);
		}
		//global_survey_related_info.media_path_data = media_file_paths;
		//global_survey_related_info.media_path_data_arr.push(media_file_paths);
		global_survey_related_info.media_path_data_arr[index] = media_file_paths;
		global_survey_related_info.media_fileEntry_arr[index].createWriter (save_media_path_data2, fail_to_write_file);
		my_log ("exit CaptureSuccess");
	};


	if (navigator.device.capture) {
		my_log ("has navigator.device.capture");
		navigator.device.capture.captureImage(
				CaptureSuccess, onFail, null);
	} else {
		my_log ("not capture available");
	}
	my_log ("exit capturePhoto2");
}

function captureAudio()
{
	navigator.device.capture.captureAudio(FileCaptureSuccess, onFail, null);
}

function captureVideo()
{
	navigator.device.capture.captureVideo(FileCaptureSuccess, onFail, null);
}    

function FileCaptureSuccess(mediaFiles)
{
	my_log ("enter FileCaptureSuccess");
	var media_file_paths = "", i=0, len = 0;
	for (i = 0, len = mediaFiles.length; i < len; i += 1) {
		my_log ("filename captured: " + mediaFiles[i].fullPath);
		media_file_paths += mediaFiles[i].fullPath + '\n';
		window.resolveLocalFileSystemURI(mediaFiles[i].fullPath, moveFile, onFail);
	}
	global_survey_related_info.media_path_data = media_file_paths;
	global_survey_related_info.current_media_capture_file_fileEntry.createWriter (save_media_path_data, fail_to_write_file);

	
}

function moveFile(fileEntry)
{      
	my_log ("entered moveFile");
	//window.resolveLocalFileSystemURI("file:///storage/sdcard0/qscript", 
	window.resolveLocalFileSystemURI(
		"file:///sdcard/" + global_survey_related_info.our_dir_path + "/incomplete/",
		function(dirEntry){
			my_log ("moving file: " + fileEntry.name + " to " + dirEntry.fullPath);
			fileEntry.moveTo(dirEntry, fileEntry.name, function(){my_log("moveFile success done");}, onFail);
		}, onFail);
}

function onFail(error)
{
	my_log("onFail: Error occured"+ error.code);
}    
