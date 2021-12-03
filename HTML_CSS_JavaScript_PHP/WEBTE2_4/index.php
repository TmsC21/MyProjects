<?php
require "Connection.php";
require "User.php";
function mainTable(){
$conn = (new Connection())->connectDatabase();
$strm = $conn->prepare("SELECT name from user_actions group by name");
$strm->execute();
$people_names = $strm->fetchAll(PDO::FETCH_CLASS,"User");
$strm = $conn->prepare("SELECT * from lectures order by timestamp");
$strm->execute();
$lectures = $strm->fetchAll(PDO::FETCH_CLASS,"User");
$strm = $conn->prepare("SELECT user_actions.lecture_id as ID,name,action, user_actions.timestamp as user_tmp,lectures.timestamp as lecture_tmp from  user_actions JOIN lectures where user_actions.lecture_id = lectures.id and name = :name and lectures.id = :lecture_id");
$strm2 = $conn->prepare("SELECT user_actions.lecture_id as ID,user_actions.timestamp as user_tmp from  user_actions JOIN lectures where user_actions.lecture_id = lectures.id ");


echo "<table class='table table-striped' id='main-table' style='border: 2px solid black'><thead>";
echo '<tr><th>Name</th>';
    foreach ($lectures as $index=>$lecture){
        echo "<th>[".($index+1)."] ".date("Y-m-d",strtotime($lecture->timestamp))."</th>";
    }
    echo "<th>Pocet ucasti</th>";
    echo "<th>Cas na prednaskach</th>";
    echo '</tr></thead><tbody>';
foreach ($people_names as $person_name){
    $countLectures = 0;
    $timeOnLecture = 0;
    $swtch_name = true;
    foreach ($lectures as $lecture) {
        if ($swtch_name) {
            echo "<tr><td>" . $person_name->name . "</td>";
            $swtch_name = false;
        }
        $lectureTime = 0;
        $strm2->execute();
        $people = $strm2->fetchAll(PDO::FETCH_CLASS, "User");
        if(!empty($people)){
            foreach ($people as $person){
                if($lecture->id == $person->ID){
                    if(strtotime($person->user_tmp) > $lectureTime){
                        $lectureTime = strtotime($person->user_tmp);
                    }
                }
            }
            $person_joined = 0;
            $person_left = 0;
            $swp_join = false;
            $swp_left = false;
            $personTimeOnLecture = 0;
            $swtch = 0;
            $strm->bindParam(":name", $person_name->name);
            $strm->bindParam(":lecture_id", $lecture->id);
            $strm->execute();
            $person = $strm->fetchAll(PDO::FETCH_CLASS, "User");
            foreach ($person as $pOnLecture){
                if (strcmp($pOnLecture->action, "Joined") == 0) {
                    $swp_join = true;
                    $person_joined = $pOnLecture->user_tmp;
                    $swtch++;
                }
                if (strcmp($pOnLecture->action, "Left") == 0) {
                    $swp_left = true;
                    $person_left = $pOnLecture->user_tmp;
                    $swtch++;
                }
                if ($swp_left == true && $swp_join == true) {
                    $personTimeOnLecture +=time_diff_minutes($person_joined,$person_left);
                    $swp_join = false;
                    $swp_left = false;
                    $swtch = 0;
                }
            }
            if ($swtch != 0) {
                $swp_left = false;
                $swp_join = false;
                $personTimeOnLecture +=time_diff_minutes($person_joined,date("H:i:s",$lectureTime));
                $str = "\"".$lecture->id."-".str_replace(" ","-",$person_name->name)."\"";
                echo "<td class='tdo' style='background-color: rgba(21,53,41,0.3)'><a style='cursor: pointer' onclick=popout(".$str.")>" . $personTimeOnLecture . "</a></td>";
                $swtch = 0;
            }else{
                $str = "\"".$lecture->id."-".str_replace(" ","-",$person_name->name)."\"";
                echo "<td class='td'><a style='cursor: pointer' onclick=popout(".$str.")>" . $personTimeOnLecture . "</a></td>";
            }
            if($personTimeOnLecture!=0){
                $countLectures++;
                $timeOnLecture+=$personTimeOnLecture;
            }

        }
    }
    echo "<td>" . $countLectures . "</td>";
    echo "<td>" . $timeOnLecture . "</td>";
    echo "</tr>";

}
}
function time_diff_minutes($start, $end){
    $start = new DateTime($start);
    $end = new DateTime($end);
    $interval = $start->diff($end);
    return ceil($interval->format('%h')*60 + $interval->format('%i') + $interval->format('%s')/60);
}

echo "</tbody></table>";
?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-eOJMYsd53ii+scO/bJGFsiCZc+5NDVN2yr8+0RDqr0Ql0h+rP48ckxlpbzKgwra6" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
    <script src="https://kit.fontawesome.com/e611225aec.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <title>Document</title>
</head>
<body>
<div id="buttons">
    <button class="btn" onclick="updateDatabase()"><i class="fas fa-sync-alt"></i></button>
    <button class="btn" onclick=visibleGraph()><i <i class="fas fa-chart-bar"></i></i></button>
</div>
<?php
 mainTable();
?>
<div style="position: sticky; top: 0">
    <div  style="width: 100%; height: 100%; z-index: 10; background-color: rgba(53,53,53,0.2); position: absolute; top: 0; left: 0; display: none" id="popout">
    </div>
</div>
<div id="cont-graph">
    <div id="graph" style="width: 100%; height: 100%; z-index: 10; background-color: rgba(53,53,53,0.5); position: absolute; top: 0; left: 0; display: none">
        <div style="width: 500px; height: 500px; background-color: white; margin: 3% auto; border: 2px solid black" >
            <canvas id="myChart" width="100" height="100"></canvas>
            <button style="margin-top: 5px" class='btn btn-secondary' onclick='disepearGraph()'>Zrusit</button>
        </div>
    </div>
</div>


<script>
    function visibleGraph(){
        document.getElementById('graph').style.display = 'block';
    }
    function disepearGraph(){
        document.getElementById('graph').style.display = 'none';
    }
    fetch("graph.php",{})
        .then((response)=>response.json())
        .then((data)=>{
            console.log(data.msg)
            var myData = data.msg;
            var labels=[];
            var datas=[];
            for(i=0;i<myData.length;i++){
                labels[i] = myData[i]["timestamp"];
                datas[i] = myData[i]["count"];
            }
            console.log(labels)
            console.log(datas)
            var ctx = document.getElementById('myChart').getContext('2d');
            var myChart = new Chart(ctx, {
                type: 'bar',
                data: {
                    labels: labels,
                    datasets: [{
                        label: '# na prednaske',
                        data: datas,
                        backgroundColor: [
                            'rgba(255, 99, 132, 0.2)',
                            'rgba(54, 162, 235, 0.2)',
                            'rgba(255, 206, 86, 0.2)',
                            'rgba(75, 192, 192, 0.2)',
                            'rgba(153, 102, 255, 0.2)',
                            'rgba(255, 159, 64, 0.2)',
                            'rgba(75, 192, 192, 1)',
                            'rgba(153, 102, 255, 1)',
                            'rgba(255, 159, 64, 1)'
                        ],
                        borderColor: [
                            'rgba(255, 99, 132, 1)',
                            'rgba(54, 162, 235, 1)',
                            'rgba(255, 206, 86, 1)',
                            'rgba(75, 192, 192, 1)',
                            'rgba(153, 102, 255, 1)',
                            'rgba(255, 159, 64, 1)',
                            'rgba(75, 192, 192, 1)',
                            'rgba(153, 102, 255, 1)',
                            'rgba(255, 159, 64, 1)'
                        ],
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true
                        }
                    }
                }
            });
        });
</script>
<script>

    function popout(index){
        fetch("popout.php",{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body:JSON.stringify({content:index})
        }).then((response)=>response.json())
            .then((data)=>{
                var myData = data.msg;
                var popout = document.getElementById("popout");
                var tbl = document.createElement("table");
                var thead = document.createElement("thead");
                var tbtr = document.createElement("tr");
                var tbth = document.createElement("th");
                var cellText = document.createTextNode("Prednaska");
                tbth.appendChild(cellText);
                tbtr.appendChild(tbth);

                var tbth = document.createElement("th");
                var cellText = document.createTextNode("Meno a priezvisko");
                tbth.appendChild(cellText);
                tbtr.appendChild(tbth);

                var tbth = document.createElement("th");
                var cellText = document.createTextNode("Stav");
                tbth.appendChild(cellText);
                tbtr.appendChild(tbth);

                var tbth = document.createElement("th");
                var cellText = document.createTextNode("Zmena stavu");
                tbth.appendChild(cellText);
                tbtr.appendChild(tbth);
                thead.appendChild(tbtr);
                tbl.appendChild(thead);
                var tblBody = document.createElement("tbody");
                    for (var j = 0; j < myData.length; j++) {
                        var row = document.createElement("tr");
                        var cell = document.createElement("td");
                        var cellText = document.createTextNode(myData[j]["lectureTimestamp"]);
                        cell.appendChild(cellText);
                        row.appendChild(cell);

                        var cell = document.createElement("td");
                        var cellText = document.createTextNode(myData[j]["name"]);
                        cell.appendChild(cellText);
                        row.appendChild(cell);

                        var cell = document.createElement("td");
                        var cellText = document.createTextNode(myData[j]["action"]);
                        cell.appendChild(cellText);
                        row.appendChild(cell);

                        var cell = document.createElement("td");
                        var cellText = document.createTextNode(myData[j]["personOnLecture"]);
                        cell.appendChild(cellText);
                        row.appendChild(cell);
                        tblBody.appendChild(row);
                }
                tbl.appendChild(tblBody);
                var dv = document.createElement("div");
                dv.innerHTML+= "<button class='btn btn-secondary' onclick='zrusitPop()'>Zrusit</button>"
                dv.setAttribute("class", "cont");
                dv.appendChild(tbl);
                popout.appendChild(dv);
                tbl.setAttribute("class", "table table-striped");
                tbl.setAttribute("border", "2px solid black");
                tbl.setAttribute("style", "background-color: white");

                popout.style.display = "block";
            });
    }
    function zrusitPop(){
        var pop = document.getElementById("popout");
        pop.style.display = "none";
        pop.removeChild(pop.childNodes[0]);
        pop.innerHTML="";
    }
    function updateDatabase(){
        alert("Vkladam do DB")
        fetch("updateDb.php",{
        }).then((response)=>response.json())
            .then((data)=>{
                alert(data.msg)
                if(data.msg !== "Table is already updated"){
                    setTimeout(()=>{ location.reload();}, 1)
                }
            });
    }
</script>
</body>
</html>
