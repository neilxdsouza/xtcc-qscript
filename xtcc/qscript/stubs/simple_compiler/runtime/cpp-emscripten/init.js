
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
	//my_log("ready to start interview");
	// var our_path = "qscript/uuid/project_name/interviewer_id/project_name_interviewer_id_serial.dat";
	// fileGetDir (our_path, printSuccess);
	//
	//
	//
	//
	//
	//if(fnVerifyCurrentUserInLocalStorage())
	//{
	//	//$.mobile.changePage( "#pageSurveys", { transition: "slideup"});
	//	showSurveys();
	//}
	//my_log ("Exit onDeviceReady");
	return true;
}

//my_log("created onDeviceReady");
document.addEventListener ("deviceready", onDeviceReady, false);
/* =========== onDeviceReady }}}1 ========= */


//my_log ("finished loading init.js");
