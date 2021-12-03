let requestData;
let swtch;
function isEmpty(str) {
    return (!str || str.length === 0 );
}
function nameDays(){
    var den = document.getElementById("den").value;
    var mesiac = document.getElementById("mesiac").value;
    var meno = document.getElementById("meno").value;
    var radios = document.querySelectorAll('input[type="radio"]:checked')[0].value;
    if(isEmpty(meno)){
        requestData = {id:radios,den:den,mesiac:mesiac}
        swtch = false;
    }
    else{
        requestData = {id:radios,meno:meno}
        swtch = true;
    }
    fetch("./apis/nameDays.php",{
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify(requestData)
    }).then((response)=>response.json())
        .then((data)=>{
            if(swtch){
                document.getElementById("nameDays").innerText ="";
                if(data.length!==0){
                    document.getElementById("nameDays").innerText += meno+" ma meniny: "+data[0]["day"]+"/"+data[0]["month"]+"\n";
                }
            }else{
                document.getElementById("nameDays").innerText ="V tento den maju meniny:\n";
                for (let i = 0; i < data.length; i++) {
                    document.getElementById("nameDays").innerText += (i+1)+"."+data[i]["name"]+"\n";
                }
            }
        })
}
function importName(){
    var den = document.getElementById("den").value;
    var mesiac = document.getElementById("mesiac").value;
    var meno = document.getElementById("meno").value;
    if(!isEmpty(meno)){
    fetch("./apis/importName.php",{
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify({meno:meno,den:den,mesiac:mesiac})
    }).then((response)=>response.json())
        .then((data)=>{alert(data["message"])})
    }else{
        alert("Meno nie je vyplnene!")
    }
}

function holiDays(){
    var radios = document.querySelectorAll('input[type="radio"]:checked')[1].value;
    if(radios==1){
        requestData = {type:"holiday",country:4}
    }else if(radios==2){
        requestData = {type:"holiday",country:5}
    }else{
        requestData = {type:"pday",country:4}
    }
    fetch("./apis/holiDays.php",{
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify(requestData)
    }).then((response)=>response.json())
        .then((data)=>{
            createTable(data)
        })
}

function createTable(data){
    var holiday = document.getElementById("holiDays");
    if(holiday.firstChild){
        holiday.removeChild(holiday.firstChild)
    }
    var tbl = document.createElement("table");
    var tblBody = document.createElement("tbody");
    var thead = document.createElement("thead");
    var th = document.createElement("th")
    var trText = document.createTextNode("Title")
    th.appendChild(trText)
    thead.appendChild(th);
    var th = document.createElement("th")
    var trText = document.createTextNode("Date(d/m)")
    th.appendChild(trText)
    thead.appendChild(th);
    tbl.appendChild(thead);
    for (var j = 0; j < data.length; j++) {
        var row = document.createElement("tr");
        var cell = document.createElement("td");
        var cellText = document.createTextNode(data[j]["name"]);
        cell.appendChild(cellText);
        row.appendChild(cell);
        var cell = document.createElement("td");
        var cellText = document.createTextNode(data[j]["day"]+"/"+data[j]["month"]);
        cell.appendChild(cellText);
        row.appendChild(cell);
        tblBody.appendChild(row);
    }
    tbl.appendChild(tblBody);
    tbl.setAttribute("border", "1");
    tbl.setAttribute("class", "table table-striped table-hover");
    holiday.appendChild(tbl);
}
function reset(){
    document.getElementById("nameDays").innerText= "";
    if(document.getElementById("holiDays").firstChild){
        document.getElementById("holiDays").removeChild(document.getElementById("holiDays").firstChild);
    }
}
