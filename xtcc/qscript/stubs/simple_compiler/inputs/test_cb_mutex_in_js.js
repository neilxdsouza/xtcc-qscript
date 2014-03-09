
	var stubs = 
		[
			{ "stub_text" : "Refridgerator", "stub_code" : 1, "mutex" : false  },
			{ "stub_text" : "AC", "stub_code" : 2 , "mutex" : false },
			{ "stub_text" : "Fan", "stub_code" : 3 , "mutex" : false },
			{ "stub_text" : "Equipped Kitchen", "stub_code" : 4 , "mutex" : false },
			{ "stub_text" : "Ensuite Bathroom", "stub_code" : 5 , "mutex" : false },
			{ "stub_text" : "None of these", "stub_code" : 6, "mutex" : true },
			{ "stub_text" : "Dont know", "stub_code" : 7, "mutex" : true }
		]
	;

	//var input_box_id_arr=[];
	var stub_info = {
		mutex_ids : {},
		non_mutex_ids : {},
		selected_ids : {}
	};
	function mutex_callback (elem)
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
			input.addEventListener ("click", mutex_callback, false);
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
	setup_cbs(stubs);
