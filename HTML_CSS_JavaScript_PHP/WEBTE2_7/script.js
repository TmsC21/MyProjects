let headers = {
    'Content-Type': 'application/json',
    "Access-Control-Allow-Origin": "*",
    "Access-Control-Allow-Methods": "DELETE, POST, GET, OPTIONS",
    "Access-Control-Allow-Headers":"Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With"
};
async function getIp(ip) {
    await fetch("https://ipinfo.io/" + ip + "?token=d887acd8fb798f", {
        method: 'GET',
        headers: headers
    }).then((response) => response.json())
        .then((data) => {
            var date = new Date().toJSON().slice(0,10);
            var time = new Date().toJSON().slice(11,19)
            var dateTime = date+" "+time;
            var divInfo = document.getElementById("personInfo")
            divInfo.innerText = "Ip adresa: " + data["ip"] + "\n" + "GPS: " + data["loc"] + "\n" + "Mesto: " + data["city"] + "\n" + "Okres: " + data["region"] + "\n" + "Stat: " + data["country"] + "\n" + "Hlavne mesto: " + data["timezone"]
            fetch("apis/importPerson.php", {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body:JSON.stringify({ip:data["ip"], loc:data["loc"], place:data["city"],state:data["country"],timestamp:dateTime})
            })
        })
}
function getWeather(ip){
    fetch("apis/getPerson.php",{
        method:"POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify({ip:ip})
    }).then((response)=>response.json())
        .then((data)=>{
            console.log()
            Weather(data["city"]);
        })
}
function Weather(city){
    console.log(city)
    fetch("https://api.openweathermap.org/data/2.5/weather?q="+city+"&appid=566d84865d8235cdc41365d8cb6ead68&units=metric",{
        method:"GET"
    }).then((response)=>response.json())
        .then((data)=>{
            document.getElementById("weather").innerHTML = '<div><div><b>'+city+'</b><br>Pocasie: '+data["weather"][0]["main"]+'<br>Pocasie presne: '+data["weather"][0]["description"]+'<br>Teplota: '+data["main"]["temp"]+'°C<br>Vietor: '+data["wind"]["speed"]+'</div><img src="http://openweathermap.org/img/wn/'+data["weather"][0]["icon"]+'@2x.png" alt="pocasie"></div>'
        })
}
function setWithExpiry(key, value, ttl) {
    const now = new Date()
    const item = {
        value: value,
        expiry: now.getTime() + ttl,
    }
    sessionStorage.setItem(key, JSON.stringify(item))
}
function getVisits(){
    fetch("apis/getVisitors.php",{
        method:"GET"
    }).then((response)=>response.json())
        .then((data)=>{
            console.log(data)
            var visitors = document.getElementById("visits");
            var tbl = document.createElement("table");
            var tblBody = document.createElement("tbody");
            var thead = document.createElement("thead");
            var th = document.createElement("th")
            var trText = document.createTextNode("Place")
            th.appendChild(trText)
            thead.appendChild(th);
            var th = document.createElement("th")
            var trText = document.createTextNode("Visits")
            th.appendChild(trText)
            thead.appendChild(th);
            tbl.appendChild(thead);
            var th = document.createElement("th")
            var trText = document.createTextNode("Flag")
            th.appendChild(trText)
            thead.appendChild(th);
            tbl.appendChild(thead);
            for (var j = 0; j < data.length; j++) {
                var row = document.createElement("tr");
                var cell = document.createElement("td");
                var cellText = document.createTextNode(data[j]["state"]);
                var is = document.createElement("i")
                is.setAttribute("onclick","showInfo('"+data[j]["state"]+"')")
                is.setAttribute("style","cursor:pointer; color:blue")
                is.appendChild(cellText)
                cell.appendChild(is);
                row.appendChild(cell);
                var cell = document.createElement("td");
                var cellText = document.createTextNode(data[j]["pocet"]);
                cell.appendChild(cellText);
                row.appendChild(cell);

                var cell = document.createElement("td");
                var img = document.createElement("img")
                img.setAttribute("src","http://www.geonames.org/flags/x/"+data[j]["state"].toLowerCase()+".gif");
                img.setAttribute("width","50");
                img.setAttribute("height","30");
                cell.appendChild(img);
                row.appendChild(cell);
                tblBody.appendChild(row);
            }
            tbl.appendChild(tblBody);
            tbl.setAttribute("border", "1");
            tbl.setAttribute("class", "table table-striped table-hover");
            visitors.appendChild(tbl);
        })
}
function checkIP(ip){
    console.log(ip)
    fetch("apis/getPerson.php",{
        method:"POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify({ip:ip})
    }).then((response)=>response.json())
        .then((data)=>{
            console.log(data)
            if(!data) {
                console.log("jaj")
                sessionStorage.clear()
            }
        })
}
function showInfo(country){
    fetch("apis/getCountryVisitors.php",{
        method:"POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body:JSON.stringify({country:country})
    }).then((response)=>response.json())
        .then((data)=>{
            console.log(data)
            var vfc = document.getElementById("visitsFromCountry")
            if(!document.getElementById("rst")){
                var btn = document.createElement("button")
                btn.setAttribute("type","button")
                btn.setAttribute("id","rst")
                btn.setAttribute("onclick","rst()")
                var cellText = document.createTextNode("reset");
                btn.appendChild(cellText)
                vfc.appendChild(btn)
            }
            var tbl = document.createElement("table");
            var tblBody = document.createElement("tbody");
            var thead = document.createElement("thead");
            var th = document.createElement("th")
            var trText = document.createTextNode("Ip")
            th.appendChild(trText)
            thead.appendChild(th);
            var th = document.createElement("th")
            var trText = document.createTextNode("Place")
            th.appendChild(trText)
            thead.appendChild(th);
            tbl.appendChild(thead);
            var th = document.createElement("th")
            var trText = document.createTextNode("GPS location")
            th.appendChild(trText)
            thead.appendChild(th);
            tbl.appendChild(thead);
            var th = document.createElement("th")
            var trText = document.createTextNode("Time connect")
            th.appendChild(trText)
            thead.appendChild(th);
            tbl.appendChild(thead);
            for (var j = 0; j < data.length; j++) {
                var row = document.createElement("tr");
                var cell = document.createElement("td");
                var cellText = document.createTextNode(data[j]["ip_address"]);
                cell.appendChild(cellText);
                row.appendChild(cell);
                var cell = document.createElement("td");
                var cellText = document.createTextNode(data[j]["state"]+"/"+data[j]["city"]);
                cell.appendChild(cellText);
                row.appendChild(cell);
                var cell = document.createElement("td");
                var img =  document.createTextNode(data[j]["GPS_loc"]);
                cell.appendChild(img);
                row.appendChild(cell);
                var cell = document.createElement("td");
                var img =  document.createTextNode(data[j]["timestamp"]);
                cell.appendChild(img);
                row.appendChild(cell);
                tblBody.appendChild(row);
            }
            tbl.appendChild(tblBody);
            tbl.setAttribute("border", "1");
            tbl.setAttribute("class", "table table-striped table-hover");
            vfc.appendChild(tbl);
        })
}
function rst(){
    var vfc = document.getElementById("visitsFromCountry")
    while(vfc.firstChild){
        vfc.removeChild(vfc.firstChild)
    }
}
function getTimestamp(){
    fetch("apis/getVisitorsTimestamp.php",{
        method:"GET"
    }).then((response)=>response.json())
        .then((data)=>{
            console.log(data)
            var t = document.getElementById("timestamp")
            var one = 0;
            var two = 0;
            var tree = 0;
            var four = 0;
            var timestamp = new Map();
            for (let i = 0; i < data.length; i++) {
                var hour = parseInt(data[i].substring(0, 2));
                var minutes = parseInt(data[i].substring(3, 5));
                if(hour >= 6 && (hour <= 14 && minutes <= 59)){
                    one++;
                    timestamp.set("6:00-15:00", one)
                }else if(hour >= 15 && (hour <= 20 && minutes <= 59)){
                    two++;
                    timestamp.set("15:00-21:00", two)
                }else if(hour >= 21 && (hour <= 23 && minutes <= 59)){
                    tree++;
                    timestamp.set("21:00-24:00", tree)
                }else if(hour >= 0 && (hour <= 5 && minutes <= 59)){
                    four++;
                    timestamp.set("24:00-6:00", four)
                }
            }
            for (let[k,v] of timestamp){
                t.innerHTML += k +" " +v+"x<br>";
            }
        })
}
function settingMap(){
    var mymap = L.map('mapid').setView([51.505, -5.09], 5);
    L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
        maxZoom: 18,
        id: 'mapbox/streets-v11',
        tileSize: 512,
        zoomOffset: -1,
        accessToken: 'pk.eyJ1IjoidG9tYXNwcmQiLCJhIjoiY2tvY3prbnZuMDRhZzJ2bDRpY3l0MmtnYiJ9.uWYMveMBBSC0G1ip6eZNYg'
    }).addTo(mymap);
    fetch("apis/getAllVisitors.php",{
        method:"GET"
    }).then((response)=>response.json())
        .then((data)=>{
            for (let i = 0; i < data.length; i++) {
                var gpsData = data[i]["GPS_loc"].split(",");
                var marker = L.marker([gpsData[0], gpsData[1]]).addTo(mymap);
                marker.bindPopup("<b>"+data[i]['city']+"/"+data[i]['state']+"</b><br>"+data[i]['ip_address']+"").openPopup()
            }

        })
}