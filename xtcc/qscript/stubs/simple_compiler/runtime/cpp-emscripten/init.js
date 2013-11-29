
//my_log ("started loading init.js");
//function onDeviceReady()
//{
//	my_log ("onDeviceReady from localStorage.js fired");
//	if(fnVerifyCurrentUserInLocalStorage())
//	{
//		//$.mobile.changePage( "#pageSurveys", { transition: "slideup"});
//		showSurveys();
//	}
//
//	/*
//	theDB = window.openDatabase("qDB", "1.0", "data_collection",1 * 1024 * 1024);
//
//	theDB.transaction(fnCheckDBTable, onTxnError, onTxnSuccess);
//	*/
//
//}


/* =========== onDeviceReady {{{1 ========= */

function onDeviceReady() {
	my_log("Enter onDeviceReady");
	var success = false;
	success = get_device_info();
	if (success == false) {
		//my_log ("Unable to get device information ... exiting the survey");
		return false;
	}
	/*
	success = get_compass_info();
	if (success == false) {
		//my_log ("Unable to get compass information ... exiting the survey");
		return false;
	}*/
	success = get_geolocation_info();
	if (success == false) {
		//my_log ("Unable to get geolocation information ... exiting the survey");
		return false;
	}
	
	getFileSystemObject();
	//if (success == false) {
	//	//my_log ("Unable to get LocalFileSystem ... exiting the survey");
	//	return false;
	//}
	// allow to click on start only after initializing all the things we need
	var return_serial_no_button = document.getElementById("btn_return_serial_no");
	return_serial_no_button.disabled = false;

	///////////////////////////////////////////////////////////////////////////////////
	var user_id = window.localStorage.getItem('userid');

	// extracting project id from link, disable line bewlo to use old JOB_NAME
	global_survey_related_info.job_name = window.location.href.split("/survey/")[1].split("/www")[0];
	var project_id = global_survey_related_info.job_name;

	global_survey_related_info.our_dir_path = "qscript/" + global_survey_related_info.device.uuid + "/" + project_id +  "/" + user_id;
	global_survey_related_info.our_dir_fullPath = global_survey_related_info.fileSystemObject.root.fullPath + "/" + global_survey_related_info.our_dir_path;
	global_survey_related_info.our_file_name = project_id + "_" + user_id + "_";
	//my_log ("Exit onDeviceReady");
	return true;
}

//my_log("created onDeviceReady");
document.addEventListener ("deviceready", onDeviceReady, false);
/* =========== onDeviceReady }}}1 ========= */


//my_log ("finished loading init.js");
