
/* =============== Logging Setup {{{1 ==================== */
	function my_log (mesg)
	{
		var div_console_log = document.getElementById("div_console_log");
		div_console_log.innerHTML += "<p>" + mesg + "</p>";
	}
	// my_log ("test log message");
/* =============== End: Logging Setup }}}1 ==================== */
my_log ("testing logging setup");
/* ===== EventUtil and FormSerialization {{{1 =============== */
/* Professional JavaScript for Web Developers - Nicholas C Zakas. Chpt 12*/
global_survey_related_info = {};
var EventUtil = {
	addHandler: function (element, type, handler) {
		if (element.addEventListener) {
			element.addEventListener (type, handler, false);
		} else if (element.attachEvent) {
			element.attachEvent ("on" + type, handler);
		} else {
			element["on" + type] = handler;
		}
	},
	getEvent: function (event) {
		return event ? event : window.event;
	},
	getTarget: function (event) {
		return event.target || event.srcElement;
	},
	preventDefault: function (event) {
		if (event.preventDefault) {
			event.preventDefault();
		} else {
			event.returnValue = false;
		}
	},
	removeHandler: function (element, type, handler) {
		if (element.removeEventListener) {
			element.removeEventListener (type, handler, false);
		} else if (element.detachEvent) {
			element.detachEvent ("on" + type, handler);
		} else {
			element["on" + type] = null;
		}
	},
	stopPropagation: function (event) {
		if (event.stopPropagation) {
			event.stopPropagation();
		} else {
			event.cancelBubble = true;
		}
	}
};

	my_log ("After EventUtil");
/* ============= }}}1 ==================*/





///* ==========  FileSystem API {{{1 ======================= */
	//my_log ("===========reached FileSystem section==========");

	//var fileSystemObject = null;
	// global Variable - current Active file
	//global_current_survey_data_file = null;
	//
	function getFileErrorHandler (file_error) {
		var file_err_string =
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
			;
		my_log ("getFileErrorHandler: " +  file_err_string);
	}
	/* getFileErrorHandler }}}2 */


	function onFileSystemSuccess (fileSystem) {
		//fileSystemObject = fileSystem;
		//my_log("assigned fileSystemObject fileSystem.name:" + fileSystem.name);
		//my_log("assigned fileSystemObject fileSystemObject.name:" +  fileSystem.name);
		//my_log("assigned fileSystemObject fileSystemObject.root.name:" +  fileSystem.root.name);
		//my_log("assigned fileSystemObject fileSystemObject.root.isDirectory:" +  fileSystem.root.isDirectory);
		global_survey_related_info.fileSystemObject = fileSystem;
		my_log("assigned fileSystemObject fileSystemObject.root.fullPath:" +  fileSystem.root.fullPath);
	}

	function fileFSError(e) {
		//console.log(e.code);
		//try {
		//	my_log ("fileFSError: " + JSON.stringify(e));
		//} catch (err) {}
		my_log ("=== ERROR ====  fileFSError: " + JSON.stringify(e));
	}

	function getFileSystemObject () {
		my_log("Enter: getFileSystemObject");
		window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onFileSystemSuccess, fileFSError);
		my_log ("After getFileSystemObject has returned");
	}

/* ==========  End: FileSystem API }}}1 ======================= */


function fileFSError(e) {
	//console.log(e.code);
	//try {
	//	my_log ("fileFSError: " + JSON.stringify(e));
	//} catch (err) {}
	my_log ("=== ERROR ====  fileFSError: " + JSON.stringify(e));
}

var fileCreatedSuccess_serno = function (file) {
	my_log ("Enter: fileCreatedSuccess_serno:" );
	//global_current_survey_data_file = file;
	global_survey_related_info.current_survey_data_file = file;
	my_log ("Exit: fileCreatedSuccess_serno:" );
};



var fnGetOrCreateDir = function (path, de, call_back) {
	my_log ("fnGetOrCreateDir path:" + path);
	var path_length = path.length;
	var entry = path.shift();
	//my_log ("fnGetOrCreateDir operating on entry:" + entry);
	if (entry) {
		if (path_length > 1) {
			de.getDirectory(entry,
					{ create : true },
					function(dirEntry) {
						my_log("success function: made dir/file: " + entry);
						fnGetOrCreateDir(path, dirEntry);
					},
					fileFSError);
		} else {
			/*
			if (create_mode.create == true) {
				my_log("reached file creation: create = true");
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
				my_log("reached file creation: open for reading only = true");
				de.getFile(entry,
						{ create : false },
						fileFoundSuccess,
					handlerFileDoesNotExist);
			}
			*/
			de.getFile (entry,
					{ create : true },
					fileCreatedSuccess_serno,
					fileFSError);
			my_log ("path_length: " + path_length + " execting fileCreatedSuccess_serno");
		}
	} else if (call_back) {
		call_back(de);
	}
};

/* readAsText {{{2 */
function readAsText(file) {
	my_log ("Enter: readAsText");
	var reader = new FileReader();
	reader.onloadend = function(evt) {
		//my_log("Read as text:");
		my_log (evt.target.result);
		//my_log ("callback_return_serial:" + callback_return_serial);
		//callback_return_serial (56, evt.target.result);
		var file_contents = document.getElementById("file_contents");
		file_contents.innerText =evt.target.result;
	};
	reader.readAsText(file);
	my_log ("Exit readAsText");
}
/* readAsText }}}2 */

function gotFile(file) {
	my_log("Enter: gotFile");
	//readDataUrl(file);
	global_survey_related_info.current_survey_data_file = file;
	readAsText(file);
}


function gotFileEntry(fileEntry) {
	my_log("Enter: gotFileEntry");
	global_survey_related_info.current_survey_data_file_entry = fileEntry;
	fileEntry.file(gotFile, getFileErrorHandler);
}


var btn_read_file = document.getElementById("btn_read_file");
EventUtil.addHandler (btn_read_file, "click", function (event) {
	my_log ("handler btn_read_file");
	var our_path = "readme-neil.txt";
	if (global_survey_related_info.fileSystemObject) {
		global_survey_related_info.fileSystemObject.root.getFile(
			our_path, {create: true} , gotFileEntry, getFileErrorHandler);
	} else {
		my_log ("fileSystemObject not available on global_survey_related_info");
	}
});

var btn_write_file = document.getElementById("btn_write_file");
EventUtil.addHandler (btn_write_file, "click", function (event) {

	var fail = function (err_msg) {
		console.log(JSON.stringify(err_msg));
		//my_log (JSON.stringify(err_msg));
		//my_log("Write fail");
	};

	var gotFileWriter = function (writer) {
		var file_contents = document.getElementById("file_contents");
		writer.write (file_contents.value); 
		//writer.write(the_survey_data);
		//my_log("Write successful");
	};
	my_log ("handler btn_write_file");
	if (global_survey_related_info.fileSystemObject && global_survey_related_info.current_survey_data_file_entry) {
		global_survey_related_info.current_survey_data_file_entry.createWriter (gotFileWriter, fail);
	} else {
		my_log ("fileSystemObject not available on global_survey_related_info");
	}
});

function onDeviceReady() {
	getFileSystemObject();
}
document.addEventListener ("deviceready", onDeviceReady, false);


