function displayTable() {
	document.getElementById("newEntryButton").addEventListener('click', function(event){
		event.preventDefault();
		addNewEntry();
	});

	var req = new XMLHttpRequest(); 
    req.open('POST', 'http://52.35.237.190:3001/table', true);
    req.addEventListener('load',function(){
    	if(req.status >= 200 && req.status < 400){
        	var response = JSON.parse(req.response);
			
	        var table = document.createElement("table");
	        table.id = "table";
	        
	        //add header row
	        var row = document.createElement("tr");
	        var td = document.createElement("th");
	        td.textContent = "Name";
	       	row.appendChild(td);
	        td = document.createElement("th");
	        td.textContent = "Reps";
	        row.appendChild(td);
	        td = document.createElement("th");
	        td.textContent = "Weight";
	        row.appendChild(td);
	        td = document.createElement("th");
	        td.textContent = "Date";
	        row.appendChild(td);
	        td = document.createElement("th");
			td.textContent = "lbs";
	        row.appendChild(td);
	        td = document.createElement("th");
			td.textContent = "EDIT/DELETE";
	        row.appendChild(td);
	        table.appendChild(row);      
	                
	        //generate rows
	        for(var i = 0; i < response.length; i++)
	        {
	        	var r = response[i];
	        	var row = generateEntryHTML(r);
	        	table.appendChild(row);
	        }

	        document.body.appendChild(table);
	    } 
		
		else {
        	console.log("Error in network request: " + req.statusText);
	    }
	});
    req.send(null);
}

function generateEntryHTML(r){
 	var row, td, button; 
 	
 	row = document.createElement("tr");
   	row.id = r["id"];
   	for(prop in r)
   	{
   		if(prop != "id") {
       		td = document.createElement("td");
       		
       		if(prop == "date") {
       			td.textContent = r[prop].substring(0,10);
       		}

       		else {
       			td.textContent = r[prop];
       		}
       		row.appendChild(td);
       	}
   	}

   	td = document.createElement("td");

   	button = document.createElement("button");
   	button.textContent = 'EDIT';
  	button.className = "space";
   	addEventListener_Edit(button, r["id"]);
	td.appendChild(button);
        	
   	button = document.createElement("button");
   	button.textContent = 'DELETE';
   	addEventListener_Delete(button, r["id"]);
   	td.appendChild(button);
   	
   	row.appendChild(td);
	    
   	return row;
}

function addEventListener_Delete(input, deleteId){
	input.addEventListener('click', function(event){
		event.preventDefault();
		
		var deletePayload = {id:deleteId};			    
		var deleteReq = new XMLHttpRequest();
		deleteReq.open('POST', 'http://52.35.237.190:3001/delete', true);
		deleteReq.setRequestHeader('Content-Type', 'application/json');
		deleteReq.addEventListener('load',function(){
			if(deleteReq.status >= 200 && deleteReq.status < 400){		       
				//remove item from table
				document.getElementById(deleteId).remove();
								      	
				//update status
				document.getElementById("status").textContent = "Entry Deleted: " + deleteReq.response;
			} 
			else {
	   			document.getElementById("status").textContent = deleteReq.status + " Error: " + deleteReq.statusText;
			 	console.log("Error in network request: " + deleteReq.statusText);
			}
		});
		deleteReq.send(JSON.stringify(deletePayload));
	});
}


function addEventListener_Edit(input, editId){
	input.addEventListener('click', function(event){
		event.preventDefault();
		document.getElementById("status").textContent = "Editing...";			    
		//show edit form
		var row = document.getElementById(editId);
		var cells = row.children;
		var curVal = cells[0].textContent;
		cells[0].textContent = "";
		var input = document.createElement("input");
		input.type = "text";
		input.id = "editName" + editId;
		input.value = curVal;
		cells[0].appendChild(input);
		
		curVal = cells[1].textContent;
		cells[1].textContent = "";
		input = document.createElement("input");
		input.type = "number";
		input.id = "editReps" + editId;
		input.value = curVal;
		cells[1].appendChild(input);

		curVal = cells[2].textContent;
		cells[2].textContent = "";
		input = document.createElement("input");
		input.type = "number";
		input.id = "editWeight" + editId;
		input.value = curVal;
		cells[2].appendChild(input);

		curVal = cells[3].textContent;
		cells[3].textContent = "";
		input = document.createElement("input");
		input.type = "date";
		input.id = "editDate" + editId;
		input.value = curVal;
		cells[3].appendChild(input);

		curVal = cells[4].textContent;
		cells[4].textContent = "";
		input = document.createElement("input");
		input.type = "radio";
		input.name = "editlbs" + editId
		input.id = "editlbs" + editId;
		input.value = "lbs";
		if(curVal == true)
		{
			input.checked = "checked";
		}
		cells[4].appendChild(input);

		var label = document.createElement("label");
		label.textContent = "lbs";
		label.for = "editlbs";
		label.className = "space";
		cells[4].appendChild(label);
		
		input = document.createElement("input");
		input.type = "radio";
		input.name = "editlbs" + editId
		input.id = "editkg" + editId;
		input.value = "kg";
		if(curVal == false)
		{
			input.checked = "checked";
		}
		cells[4].appendChild(input);
		var label = document.createElement("label");
		label.textContent = "kg";
		label.for = "editkg";
		cells[4].appendChild(label);
		cells[5].innerHTML = "<input type='submit' value='Save Changes' id='saveChanges" + editId + "' />";
		document.getElementById("saveChanges" + editId).addEventListener('click', function(event){
			
			var editPayload = {id: editId,
							   name:document.getElementById("editName" + editId).value, 
							   reps:document.getElementById("editReps" + editId).value , 
							   weight:document.getElementById("editWeight" + editId).value, 
							   date:document.getElementById("editDate" + editId).value.substring(0,10),
							   lbs:document.getElementsByName("editlbs" + editId)[0].checked};

			var editReq = new XMLHttpRequest();
			editReq.open('POST', 'http://52.35.237.190:3001/edit', true);
			editReq.setRequestHeader('Content-Type', 'application/json');
			editReq.addEventListener('load',function(){
				if(editReq.status >= 200 && editReq.status < 400){
					
					var updated = JSON.parse(editReq.response);
					
					var row = document.getElementById(editId);
					var td;
					//update item from table			       
					row.innerHTML = "";

					for(prop in updated)
				   	{
				   		if(prop != "id") {
				       		td = document.createElement("td");
				       		
				       		if(prop == "date") {
				       			td.textContent = updated[prop].substring(0,10);
				       		}

				       		else {
				       			td.textContent = updated[prop];
				       		}
				       		row.appendChild(td);
				       	}
				   	}

				   	td = document.createElement("td");

				   	button = document.createElement("button");

				  	button.textContent = 'EDIT';
				  	button.className = "space";
				   	addEventListener_Edit(button, updated["id"]);			        	
					td.appendChild(button); 	
				   	
				   	button = document.createElement("button");
				   	button.textContent = 'DELETE';
				   	addEventListener_Delete(button, updated["id"]);
				   	td.appendChild(button);
				   	
				   	row.appendChild(td);
													      	
					//update status
					document.getElementById("status").textContent = "Entry Updated: " + editReq.response;	
				} 
				else {
		   			document.getElementById("status").textContent = editReq.status + " Error: " + editReq.statusText;
				 	console.log("Error in network request: " + editReq.statusText);
				}
			});
			editReq.send(JSON.stringify(editPayload));
		});	
	});
}

function addNewEntry(){
	var form = document.createElement("form");
	form.id = "newEntry";

	var label = document.createElement("label");
	label.textContent = "Name: ";
	form.appendChild(label);
	var input = document.createElement("input");
	input.type = "text";
	input.id = "name";
	input.className = "space";
	form.appendChild(input);
	
	label = document.createElement("label");
	label.textContent = "Reps: ";
	form.appendChild(label);
	input = document.createElement("input");
	input.type = "number";
	input.id = "reps";
	input.className = "space";
	form.appendChild(input);
	
	label = document.createElement("label");
	label.textContent = "Weight: ";
	form.appendChild(label);
	input = document.createElement("input");
	input.type = "number";
	input.id = "weight";
	input.className = "space";
	form.appendChild(input);
	
	input = document.createElement("input");
	input.type = "radio";
	input.name = "lbs";
	input.value = "lbs";
	input.checked = "checked";
	form.appendChild(input);
	label = document.createElement("label");
	label.textContent = "lbs";
	label.className = "space";
	form.appendChild(label);

	input = document.createElement("input");
	input.type = "radio";
	input.name = "lbs";
	input.value = "kg";
	form.appendChild(input);
	label = document.createElement("label");
	label.textContent = "kg";
	label.className = "space";
	form.appendChild(label);

	label = document.createElement("label");
	label.textContent = "Date: ";
	form.appendChild(label);
	input = document.createElement("input");
	input.type = "date";
	input.id = "date";
	input.className = "space";
	form.appendChild(input);
	
	input = document.createElement("input");
	input.type = "submit";
	input.value = "Add";
	input.addEventListener('click', function(event) {
		event.preventDefault();
					    
	   	var newEntry = {name:document.getElementById("name").value, 
	   					reps:document.getElementById("reps").value , 
	   					weight:document.getElementById("weight").value, 
	   					date:document.getElementById("date").value.substring(0,10),
	   					lbs:document.getElementsByName("lbs")[0].checked};
		
		var addReq = new XMLHttpRequest();
		addReq.open('POST', 'http://52.35.237.190:3001/add', true);
		addReq.setRequestHeader('Content-Type', 'application/json');
		addReq.addEventListener('load',function(){
			if(addReq.status >= 200 && addReq.status < 400){
				var added = JSON.parse(addReq.response);
				//add element to table
				document.getElementById("table").appendChild(generateEntryHTML(added));    	
				document.getElementById("status").textContent = "Entry Added: " + addReq.response;
			} 
			else {
	   			document.getElementById("status").textContent = addReq.status + " Error: " + addReq.statusText;
			 	console.log("Error in network request: " + addReq.statusText);
			}
		});
		//add entry to database
		addReq.send(JSON.stringify(newEntry));
		document.getElementById("newEntryButton").style.visibility = "visible";
		document.getElementById("newEntry").remove();
	});
	form.appendChild(input);
	
	document.getElementById("newEntryButton").style.visibility = "hidden";
	document.getElementById("newEntryPlaceholder").appendChild(form);
}

