var authStatus=false;

//my_log ("started loading localStorage.js");

function fnVerifyCurrentUserInLocalStorage()
{
	var retVal = false;

	var JobjCurrLogIn = fnGetCurrentLoggedUser();
	var JobjAllDeviceUsers = fnGetAllDeviceUsers();

	//check if the current logged In user is is list of all logged in users
	//if YES, the go to survey list page
	//if NO, remain on LoginSignUp screen
	//for each object in AllDeviceUsers, get the UserName and compare with CuurLogIn user
	//if match is found then great

	if(JobjCurrLogIn.UserName!="")
	{
		$.each(JobjAllDeviceUsers,function(index,item){

			if(item.UserName!="" && item.UserName==JobjCurrLogIn.UserName)
			{

				retVal=true;//set the value to true as user is found
				return false;//break out of for each loop
			}
		});
	}

	return retVal;
}

//my_log ("created fnVerifyCurrentUserInLocalStorage");

function fnGetCurrentLoggedUser()
{

	var retVal = window.localStorage.getItem("curr_loggedIn_user");

	if(!retVal)
	{
	var CurrObjTemplate = {
		"UserName":"",
		"LogInTime":""
	};
	window.localStorage.setItem("curr_loggedIn_user",JSON.stringify(CurrObjTemplate));

	retVal = window.localStorage.getItem("curr_loggedIn_user");
	}

	return JSON.parse(retVal);
}
//my_log ("created fnGetCurrentLoggedUser");

function fnSetCurrentLoggedUser(username)
{

	var CurrObjTemplate = {
		"UserName":username,
		"LogInTime":$.now()
	};

	window.localStorage.setItem("curr_loggedIn_user",JSON.stringify(CurrObjTemplate));
}

//my_log ("created fnSetCurrentLoggedUser");

function fnCheckAndAddUserToDeviceUsers(username,pwd)
{

	var currDeviceUsers = fnGetAllDeviceUsers();

	var allreadyAdded = false;
	if(username!="")
	{
		$.each(currDeviceUsers,function(index,item){

			if(item.UserName!="" && item.UserName==username)
			{
				item.Pin = pwd;	
				return false;//break out of for each loop
			}
		});

		if(!allreadyAdded)
		{
			var newUser = {};
			newUser["UserName"]=username;
			newUser["Pin"]=pwd;
			currDeviceUsers.push(newUser);
		}
		window.localStorage.setItem("allDevice_users",JSON.stringify(currDeviceUsers));
	}
}
//my_log ("created fnCheckAndAddUserToDeviceUsers");

function fnGetAllDeviceUsers()
{
	var retVal = window.localStorage.getItem("allDevice_users");
	
	if(!retVal)
	{
		var CurrObjTemplate = [
			{"UserName":"","Pin":""}
		];
		window.localStorage.setItem("allDevice_users",JSON.stringify(CurrObjTemplate));

		retVal = window.localStorage.getItem("allDevice_users");
	}
	return JSON.parse(retVal);
}
//my_log ("created fnGetAllDeviceUsers");

$(document).ready(function(){
	//check local storage for logged in person
	//

	$("#popupUndismissible").bind({
	   popupafterclose: function(event, ui) {
	   	if(!global_survey_related_info.position)
	   	{
	   		$("#selectGPS").val("off").slider("refresh");
	   	}
	   }
	});

	$("#btnLogout").click(function(){
	//clear current logged in user and navigate to first page
	window.localStorage.removeItem("curr_loggedIn_user");
	//$.mobile.changePage( "#pageLoginSignUp", { transition: "slideup"});
	window.location.reload(true);
	});

	$("#btnlogin").click(function(){
		//check if the fields txtName and txtPassword are filled
		var name = $("#txtname").val();
		var pwd = $("#txtpassword").val();
		if(name=="" || pwd=="")
		{
			alert("Please provide credentials");			
		}
		else
		{
			$.mobile.loading("show");
			fnVerifyUserInformation(name,pwd)
			.done(function(response) 
			{
				$.mobile.loading("hide");

			  if(response.success) 
			  {
				//$.mobile.changePage( "#pageSurveys", { transition: "slideup"});
			  	fnSetCurrentLoggedUser(name);
			  	fnCheckAndAddUserToDeviceUsers(name,pwd);				
				showSurveys();
			  } 
			  else 
			  {
			      alert(response.messages);
			  }
			})
			.fail(function(err) 
			{
				$.mobile.loading("hide");
			     alert(response.messages);
			});

		}

	});

	$("#btnSignUp").click(function(){
		//verify all fields
		var fieldValidity = fnCheckLocalFieldsValidity();

		if(!fieldValidity.error)
		{
			//get these values name,pwd,fname,uuid
			//get local fields
			var username = $("#txtusername").val(),
				pwd = $("#txtpwd").val(),
				fname = $("#txtfullname").val(),
				uuid = fnGetDeviceUUID();

			$.mobile.loading("show");

			fnAddNewUserInformation(username,pwd,fname,uuid)
			.done(function(response) 
			{
				$.mobile.loading("hide");

			  if(!response.error)
			  {
			  	//store the information in local storage
			  	fnSetCurrentLoggedUser(username);
				//$.mobile.changePage( "#pageSurveys", { transition: "slideup"});
			  	fnCheckAndAddUserToDeviceUsers(username,pwd);				
				showSurveys();
			  } 
			  else 
			  {			  	
			    $("#divpopinfoSignUp").find("p").html(response.messages);
			    $("#divpopinfoSignUp").popup( "open");
			  }
			})
			.fail(function(err) 
			{
				$.mobile.loading("hide");			    
			    $("#divpopinfoSignUp").find("p").html(response.messages);
			});

		}
		else
		{
			var errMsgs = fieldValidity.messages.join("<br/>");
			$("#divpopinfoSignUp").find("p").html(errMsgs);
			$("#divpopinfoSignUp").popup("open");
		}
	});


});

//my_log ("created document.ready");

function fnGetDeviceUUID()
{
	return device.uuid;
}

//my_log ("created fnGetDeviceUUID");

function fnCheckLocalFieldsValidity()
//returns JSON based on the field validity
{
	var retVal = {"error":true,"messages":[]};
	try
	{
		//check txtfullname
		//check txtusername
		//check txtpwd
		//check txtconfirmpwd
		var username = $.trim($("#txtusername").val()),
		pwd = $.trim($("#txtpwd").val()),
		cpwd = $.trim($("#txtconfirmpwd").val()),
		fname = $.trim($("#txtfullname").val());
		//var emailRegex = /^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/;
		var emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
		var isEmailValid = username.match(emailRegex);

		if(username.length>0 && pwd.length>=6 && pwd==cpwd && fname.length>0 && isEmailValid)
		{
			retVal.error=false;	
		}

		if(fname.length==0)
		{
			retVal.messages.push("Please enter an valid name");
		}
		if(!isEmailValid)
		{
			retVal.messages.push("Please enter an email ID");
		}
		if(pwd.length<6)
		{
			retVal.messages.push("Please enter a password with length greater than 6");
		}
		if(cpwd.length<6)
		{
			retVal.messages.push("Please enter a confirm password with length greater than 6");
		}
		if(pwd!=cpwd)
		{
			retVal.messages.push("Password and confirm password do not match");
		}		

	}
	catch(err)
	{
		alert("error in function fnCheckLocalFieldsValidity");
	}
	return retVal;
}

//my_log ("created fnCheckLocalFieldsValidity");


function fnAddNewUserInformation(username,pwd,fname,uuid)
{
  var connectionType = fnGetConnection(),
      valid = false,
      retVal = {"error":true,"messages":[]},
      dfd = $.Deferred();

  try
  {
	if(connectionType==Connection.WIFI ||
	connectionType==Connection.CELL_2G ||
	connectionType==Connection.CELL_3G ||
	connectionType==Connection.CELL_4G)
	{

		var url = "http://qscript.co/signup";
		var data = {
			"emailId":username,
			"password":pwd,
			"fname":fname,
			"uuid":uuid
		};

		var postData = 	$.ajax({
					  type: "POST",
					  url: url,
					  data:data
					});

		postData.success(function(data){

			if(data.error)
			{
				retVal.messages.push(data.message);
				dfd.resolve(retVal);
			}
			else
			{
				retVal.error = false;
				retVal.messages.push(data.message);
				dfd.resolve(retVal);
			}

		});

		postData.fail(function(data){
			retVal.messages.push(data.message);		
			dfd.reject(retVal);
		});		

	}
	else
	{
		retVal.messages.push("Internet connection unavailable. Please try later.");
		dfd.resolve(retVal);
	}  	
  }
  catch(err)
  {
	retVal.messages.push("failing in function fnAddNewUserInformation");
	dfd.resolve(retVal);
  }

  return dfd.promise();

}

//my_log ("created fnAddNewUserInformation");

function fnVerifyUserInformation(username,pwd)
{
  var connectionType = fnGetConnection(),
      valid = false,
      retMessages = [],
      dfd = $.Deferred();

if(connectionType==Connection.WIFI ||
connectionType==Connection.CELL_2G ||
connectionType==Connection.CELL_3G ||
connectionType==Connection.CELL_4G)
{


	var url = "http://qscript.co/login";
	var data = {
		"emailId":username,
		"password":pwd,
		"uuid":fnGetDeviceUUID(),
	};

	var postData = 	$.ajax({
				  type: "POST",
				  url: url,
				  data:data
				});

	postData.success(function(data){

		if(data.error)
		{
			retMessages.push(data.message);
			dfd.resolve({success: false,messages: retMessages});
		}
		else
		{
			retMessages.push(data.message);
			dfd.resolve({success: true,messages: retMessages});
		}		

	});

	postData.fail(function(data){
		retMessages.push(data.message);		
		dfd.reject({success: true,messages: retMessages});
	});



}
else
{
	//check with local storage
	var JobjAllDeviceUsers = fnGetAllDeviceUsers();
	if(username!="")
	{
		$.each(JobjAllDeviceUsers,function(index,item){

			if(item.UserName!="" && item.UserName==username &&
				item.Pin==pwd)
			{
				valid = true;
				return false;//break out of for each loop
			}
		});

		if(valid)
		{
			retMessages.push("Client authentication successful");
			dfd.resolve({success: true,messages: retMessages});			
		}
		else
		{
			retMessages.push("Client authentication failed");
			dfd.resolve({success: false,messages: retMessages});
		}
	}
}

  return dfd.promise();
}

//my_log ("created fnVerifyUserInformation");



function fnGetConnection() {

    return navigator.network.connection.type;    
}
//my_log ("created fnGetConnection");

/* welcome page buttons */
function goToHome(){

$('#welcome_section').show();
$('#login_section').hide();
$('#signup_section').hide();

}
//my_log ("created goToHome");

function goToLogin() {
	$('#welcome_section').hide();
	$('#login_section').show();
	$("#iconHeaderLeft").removeClass("icon-reorder").addClass("icon-chevron-left");	
}
//my_log ("created goToLogin");


function goToSignUp() {
	$('#welcome_section').hide();
	$('#signup_section').show();
	$("#iconHeaderLeft").removeClass("icon-reorder").addClass("icon-chevron-left");		
}
//my_log ("created goToSignUp");


function showSurveys() {
	$('#auth_section').html('');
	$('#auth_section').hide();
	$('#div_serial_no').show();

	// show current logged in user
	var loggedInUser = window.localStorage.getItem('curr_loggedIn_user');
	if(loggedInUser) {
		$('#curr_loggedIn_user').html('Logged in as:<br/>' + JSON.parse(loggedInUser).UserName);
	}
	else {
		$('#curr_loggedIn_user').html('Logout from the Application');
	}
}
//my_log ("created showSurveys");

//my_log ("finished loading localStorage.js");
