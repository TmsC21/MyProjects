function tlacidlo(vall){
    let inputX = document.getElementById("inputX").value;
    let inputY = document.getElementById("inputY").value;
    if(vall === true){
        if((inputX < 10 && inputX >= 1) && (inputY < 10 && inputY >= 1)){
            document.getElementsByClassName("Alert")[0].style.display = "none";
            document.getElementById("Hlav_tlac").type = "submit";
            document.getElementById("tab").style.display = "flex";
            document.getElementById("inputX").style.border = "2px solid green";
            document.getElementById("inputY").style.border = "2px solid green";
            genTable();
        }
        else{
            if(inputX > 9 || inputX < 1){
                document.getElementById("inputX").style.border = "2px solid red";
            }
            if(inputY > 9 || inputY < 1){
                console.log("red")
                document.getElementById("inputY").style.border = "2px solid red";
            }
            document.getElementsByClassName("Alert")[0].style.display = "block";
            document.getElementById("tab").style.display = "none";
        }
    }
    else{
        document.getElementById("tab").style.display = "none";
        const myNode = document.getElementById("table-container");
        while (myNode.firstChild) {
            myNode.removeChild(myNode.lastChild);
        }
    }
}
function genTable(){
    let table = document.createElement("table");
    let inputX = document.getElementById("inputX").value;
    let inputY = document.getElementById("inputY").value;
    for (let i = 0; i <= inputY; i++) {
        let row = document.createElement("tr");
        for (let j = 0; j <= inputX; j++) {
            let col = document.createElement("td");
                if(i===0&&j===0){
                    row.appendChild(col);
                }
                else if(j === 0){
                    row.appendChild(col);
                    col.append('Y='+i);
                }
                else if(i === 0){
                    row.appendChild(col);
                    col.append('X='+j);
                }
                if(i!==0 && j!==0){
                    row.appendChild(col);
                    col.append((i*j).toString());
                }
        }
        table.appendChild(row);
    }
    document.getElementById("table-container").appendChild(table);
}