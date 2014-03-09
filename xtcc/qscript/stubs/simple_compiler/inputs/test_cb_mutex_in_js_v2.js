
	var stubs = 
		[ {
			"stub_name" : "amen" ,
			"stub_data" :  [
				{ "stub_text" : "Refridgerator", "stub_code" : 1, "mutex" : false  },
				{ "stub_text" : "AC", "stub_code" : 2 , "mutex" : false },
				{ "stub_text" : "Fan", "stub_code" : 3 , "mutex" : false },
				{ "stub_text" : "Equipped Kitchen", "stub_code" : 4 , "mutex" : false },
				{ "stub_text" : "Ensuite Bathroom", "stub_code" : 5 , "mutex" : false },
				{ "stub_text" : "None of these", "stub_code" : 6, "mutex" : true },
				{ "stub_text" : "Dont know", "stub_code" : 7, "mutex" : true }
			]
			},
			{
			"stub_name" :  "plc_of_int",
			"stub_data" : [
				{ "stub_text" : "Museum", "stub_code" : 1, "mutex": false },
				{ "stub_text" : "Architectural site", "stub_code" : 2, "mutex": false },
				{ "stub_text" : "Clubs/Dicos", "stub_code" : 3, "mutex": false },
				{ "stub_text" : "Lake", "stub_code" : 4, "mutex": false },
				{ "stub_text" : "Waterfall", "stub_code" : 5, "mutex": false },
				{ "stub_text" : "None of these", "stub_code" : 6, "mutex": true }
			]
			}
		]
	
	;


	function curry(fn){
		var args = Array.prototype.slice.call(arguments, 1);
		return function() {
			var innerArgs = Array.prototype.slice.call(arguments),
					finalArgs = args.concat(innerArgs);
			return fn.apply(null, finalArgs);
		};
	}

	//var input_box_id_arr=[];
	var stub_info = {};

	var question_data = [ 
		{"qname" : "q1", "stub_name" : "plc_of_int" },
		{"qname" : "q2", "stub_name" : "amen" }
		]
	;

	/*
	function mutex_callback (stub_list, elem)
	{
		console.log ("mutex_callback: id", this.id);
		//var i = 0, e;
		//for (i = 0; i < input_box_id_arr.length; ++i) {
		//	e = document.getElementById(input_box_id_arr[i]);
		//	if (this.id !== elem.id && e.checked ) {
		//		e.checked = false;
		//	}
		//}
		//this.checked = true;
		//var p;
		//console.log ("non_mutex_ids");
		//for (p in stub_info.non_mutex_ids) {
		//	console.log (p);
		//}
		//console.log ("mutex_ids");
		//for (p in stub_info.mutex_ids) {
		//	console.log (p);
		//}
		var p, e;
		if (this.id in stub_info.mutex_ids) {
			for (p in stub_info.selected_ids) {
				e = document.getElementById(p);
				e.checked = false;
			}
			stub_info.selected_ids = {};
			stub_info.selected_ids[this.id] = true;
		} else {
			// this should run only once in case the
			// previous selection was a mutex field
			// if our code is bugfree
			for (p in stub_info.selected_ids) {
				if (p in stub_info.mutex_ids) {
					e = document.getElementById(p);
					e.checked = false;
					delete stub_info.selected_ids[p];
				}
			}
			this.checked = true;
			stub_info.selected_ids[this.id] = true;
		}
	}
	*/

	/*
	function Person(name, age, job){
		//create the object to return
		var o = new Object();
		//optional: define private variables/functions here
		//attach methods
		o.sayName = function(){
			alert(name);
		};
		//return the object
		return o;
	}
	*/


	function mutex_callback_v2 (elem, question_name )
	{
		console.log ("mutex_callback: id", elem.id);
		//var i = 0, e;
		//for (i = 0; i < input_box_id_arr.length; ++i) {
		//	e = document.getElementById(input_box_id_arr[i]);
		//	if (this.id !== elem.id && e.checked ) {
		//		e.checked = false;
		//	}
		//}
		//this.checked = true;
		var p;
		var	e,
			p_stub_info = stub_info[question_name];
		console.log ("non_mutex_ids");
		for (p in p_stub_info.non_mutex_ids) {
			console.log (p);
		}
		console.log ("mutex_ids");
		for (p in p_stub_info.mutex_ids) {
			console.log (p);
		}
		 
		if (elem.id in p_stub_info.mutex_ids) {
			for (p in p_stub_info.selected_ids) {
				e = document.getElementById(p);
				e.checked = false;
			}
			p_stub_info.selected_ids = {};
			p_stub_info.selected_ids[elem.id] = true;
		} else {
			// this should run only once in case the
			// previous selection was a mutex field
			// if our code is bugfree
			for (p in p_stub_info.selected_ids) {
				if (p in p_stub_info.mutex_ids) {
					e = document.getElementById(p);
					e.checked = false;
					delete p_stub_info.selected_ids[p];
				}
			}
			elem.checked = true;
			p_stub_info.selected_ids[elem.id] = true;
		}
		console.log( "mutex_callback_v2 question_name: ", question_name); 
	}


	function setup_cbs(stubs) {
		var	input, i=0, 
			doc_frag2 = document.createDocumentFragment(),
			my_li;
		//input_box_id_arr.length = 0;
		for (i=0; i<stubs.length; ++i) {
			input = document.createElement ("input");
			var id_text = "cb_" + stubs[i].stub_code;
			input.id = id_text;
			input.type = "checkbox";
			//input_box_id_arr.push(id_text);
			if (stubs[i].mutex === true) {
				input.dataset.mutex = true;
				stub_info.mutex_ids[id_text] = true;
			} else {
				input.dataset.mutex = false;
				stub_info.non_mutex_ids[id_text] = true;
			}
			//var fn = make_curriefunc ( mutex_callback , question_name);
			input.addEventListener ("click", fn, false);
			//input.addEventListener ("click", mutex_callback, false);
			var input_label = document.createElement("label");
			input_label.innerHTML = stubs[i].stub_text;
			input_label.setAttribute("for", id_text);
			my_li = document.createElement("span");
			my_li.appendChild(input);
			my_li.appendChild(input_label);
			doc_frag2.appendChild(my_li);
		}
		var id_content = document.getElementById("id_content");
		id_content.appendChild(doc_frag2);
	}
	//setup_cbs(stubs);


	function setup_cbs_v2(question_obj, stubs) {
		console.log ("Enter: setup_cbs_v2");
		var	input, i=0, 
			doc_frag2 = document.createDocumentFragment(),
			my_li;
		var current_stubs = null;
		for (i = 0; i < stubs.length; ++i) {
			if (stubs[i].stub_name == question_obj.stub_name) {
				current_stubs = stubs[i];
				console.log ("found stub_name: ", current_stubs.stub_data.length);
				break;
			}
		}
		if (current_stubs === null) {
			console.log("returning current_stubs === null");
			return;
		}
		//input_box_id_arr.length = 0;
		var question_name = question_obj.qname;
		console.log ("reached here: created curry fn with question_name:", question_name);
		//mutex_callback_qn();
		stub_info[question_name] = { mutex_ids: {}, non_mutex_ids: {}, selected_ids: {} };
		for (i=0; i<current_stubs.stub_data.length; ++i) {
			console.log ("iter: ", i);
			input = document.createElement ("input");
			var id_text = question_name + "_cb_" + current_stubs.stub_data[i].stub_code;
			input.id = id_text;
			input.type = "checkbox";
			//input_box_id_arr.push(id_text);
			if (current_stubs.stub_data[i].mutex === true) {
				//input.dataset.mutex = true;
				stub_info[question_name].mutex_ids[id_text] = true;
			} else {
				//input.dataset.mutex = false;
				stub_info[question_name].non_mutex_ids[id_text] = true;
			}
			var mutex_callback_qn = curry (mutex_callback_v2, input, question_name);
			input.addEventListener ("click", mutex_callback_qn, false);
			//input.addEventListener ("click", mutex_callback, false);
			var input_label = document.createElement("label");
			input_label.innerHTML = current_stubs.stub_data[i].stub_text;
			input_label.setAttribute("for", id_text);
			my_li = document.createElement("span");
			my_li.appendChild(input);
			my_li.appendChild(input_label);
			doc_frag2.appendChild(my_li);
		}
		var id_content = document.getElementById("id_content");
		id_content.appendChild(doc_frag2);
		id_content.appendChild(document.createElement("p"));
		console.log ("Exit: setup_cbs_v2");
	}

function display_questions(question_data)
{
	var i=0;
	for (i=0; i < question_data.length; ++i) {
		console.log("setting up question: " + question_data[i].qname);
		setup_cbs_v2 (question_data[i], stubs);
	}
}
display_questions(question_data);
