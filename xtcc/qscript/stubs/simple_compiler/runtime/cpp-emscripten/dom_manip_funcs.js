mergeInto(LibraryManager.library, {

print_to_question_area: function (question_text_ptr)
{
	//alert("print_to_question_area: " + i );
	var the_question_text = Pointer_stringify (question_text_ptr);
	var v = document.getElementById("question_text_area");
	var html = "";
	html +=
		"<p>"
		+ the_question_text
		+ "</p>";
	v.innerHTML = html;
},

print_to_stub_area: function (ptr_question_type, no_mpn, ptr_stub_info, counter)
{
	//my_log ("print_to_stub_area");
	//alert ("print_to_stub_area");
	//alert("print_to_question_area: " + i );
	//var v = document.getElementById("stubs_form_div");
	var question_type = Pointer_stringify (ptr_question_type);
	var stubs_form_div = document.getElementById("stubs_form_div");
	var the_stub_data = Pointer_stringify (ptr_stub_info);

	var clear_prev_node_sub_child = function (node) {
		var n_child_nodes = node.childNodes.length;
		for (var i1 = n_child_nodes-1; i1 >= 0; --i1) {
			node.removeChild(node.childNodes[i1]);
		}
	};


	var display_stubs = function (question_type, json_rep2) {
		var doc_frag2 = document.createDocumentFragment();
		if (question_type === "nq") {
			var res2 = JSON.parse(json_rep2);
			//alert (res2.name);
			//alert (res2.stubs);
			var my_li = null;
			for (var i=0; i<res2.stubs.length;  ++i) {
				if (res2.stubs[i].mask == 1) {
					var input   = document.createElement("input");
					if (no_mpn == 1) {
						input.type  = "radio";
						//input.setAttribute("data-dojo-type", "dojox/mobile/RadioButton");
						//input.setAttribute("data-dojo-type", "dijit/form/RadioButton");
						input.setAttribute("data-dojo-type", "dojox/mobile/RadioButton");
					} else {
						input.type  = "checkbox";
						//input.setAttribute("data-dojo-type", "dojox/mobile/CheckBox");
						//input.setAttribute("data-dojo-type", "dijit/form/CheckBox");
						input.setAttribute("data-dojo-type", "dojox/mobile/CheckBox");
						//input.setAttribute("class", "custom");
						input.style.class="custom";
					}
					//input.name  = "stub_response";
					input.name  = "radio-choice";
					input.value = res2.stubs[i].stub_code;
					var id_text = res2.name + res2.stubs[i].stub_code + "_" + counter;
					//alert("id_text: " + id_text);
					input.id  = id_text;
					//alert ("id_text:" + id_text);
					var input_label   = document.createElement("label");
					input_label.innerHTML = res2.stubs[i].stub_text;
					input_label.setAttribute("for", id_text);
					my_li = document.createElement("li");
					my_li.appendChild(input);
					my_li.appendChild(input_label);
					my_li.setAttribute("data-dojo-type", "dojox/mobile/ListItem");
					doc_frag2.appendChild(my_li);
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
			clear_prev_node_sub_child (stubs_form_div);

			stubs_form_div.appendChild(doc_frag2);



		} else {
			var input_text = document.createElement("input");
			input_text.type  = "text";
			doc_frag2.appendChild(input_text);
			input_text.setAttribute("data-dojo-type", "dojox/form/TextBox");
			clear_prev_node_sub_child (stubs_form_div);
			stubs_form_div.appendChild(doc_frag2);
		}

		//$( '#stubs_form_div' ).trigger( 'updatelayout' );
		$( '#stubs_form_div' ).trigger( 'create' );
		/*
		require([
			 "dojo/parser",
			 "dojox/mobile/parser",
			 "dojo/dom",
			 "dojox/mobile",
			 "dojox/mobile/deviceTheme",
			 "dojox/mobile/compat",
			 "dojo/domReady!"
		],
		function(parser, dom) {
			parser.parse({
				rootNode: stubs_form_div
			});
		});
		*/

	};


	display_stubs (question_type, the_stub_data);

},


/*
get_serial_no_from_dom: function (){
	var serial_no_input = document.getElementById("serial_no_input");
	// for now hardcode a serial no = 1001
	serial_no_input = 1001;
	return serial_no_input;
}
*/

save_qnre_data: function (survey_data_ptr)
{
	alert ("Enter: save_qnre_data ");
	var the_survey_data = Pointer_stringify (survey_data_ptr);
	var fail = function (err_msg) {
		console.log(JSON.stringify(err_msg));
		my_log (JSON.stringify(err_msg));
	};

	var gotFileWriter = function (writer) {
		writer.write(the_survey_data);
	};

	if (global_current_survey_data_file) {
		global_current_survey_data_file.createWriter (gotFileWriter, fail);
	} else {
		my_log ("global_current_survey_data_file not available from dom_manip_funcs.js");
	}
},

show_end_of_qnre_page: function() {
	var div_serial_no = document.getElementById("div_serial_no");
	div_serial_no.style.display = "none";
	var question_view = document.getElementById("question_view");
	question_view.style.display = "none";
	var thank_you_screen = document.getElementById("thank_you_screen");
	thank_you_screen.style.display = "block";
}

});
