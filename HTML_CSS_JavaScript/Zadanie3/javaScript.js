function radios(){
    const ano = document.getElementById("gridRadios1")
    const nie = document.getElementById("gridRadios2")

    ano.onchange = function (){
        document.getElementsByClassName("textArea")[0].style.display = 'none'
        document.getElementsByClassName("novyContainer")[0].style.display = 'block'
        document.getElementById("gridRadios2").checked = false
    }
    nie.onchange = function (){
        document.getElementsByClassName("novyContainer")[0].style.display = 'none'
        document.getElementsByClassName("textArea")[0].style.display =  'block'
        document.getElementById("gridRadios1").checked = false
    }
}
function checkBox(){
    const check = document.getElementById("ine")
    if(check.checked === true){
        document.getElementsByClassName("textIne")[0].style.display = "block"
    }
    else{
        document.getElementsByClassName("textIne")[0].style.display = "none"
    }
}
function validEmail(){
    let regex = new RegExp("^[A-Za-z0-9._%+-]{3,}@[a-zA-Z-]{3,}([.]{1}[a-zA-Z]{2,4}|[.]{1}[a-zA-Z]{2,}[.]{1}[a-zA-Z]{2,4})$");

    let mail = document.getElementById("inputEmail").value;
    if(mail.match(regex)){
        document.getElementsByClassName("pravda_email")[0].style.border = "3px solid green";
        document.getElementsByClassName("small_email")[0].style.display = "none";
        return 1;
    }
    else{
        document.getElementsByClassName("nepravda_email")[0].style.border = "3px solid red";
        document.getElementsByClassName("small_email")[0].style.display = "block";
        return 0;
    }
}
function datum(){
    let datumInput = new Date(document.getElementById("inputDatum").value);
    let datumNow = new Date();
    let inputRok = document.getElementById("inputVek").value;
    let vys;
    let diff;
    let rok = 1000 * 60 * 60 * 24 * 30 * 12;
    diff = datumNow - datumInput;
    vys = Math.floor(diff / rok);

    if(vys == inputRok){
        document.getElementsByClassName("pravda_date")[0].style.border = "3px solid green";
        document.getElementsByClassName("pravda_date")[1].style.border = "3px solid green";
        document.getElementsByClassName("small_datum")[0].style.display = "none";
        return 1;
    }
    else{
        document.getElementsByClassName("nepravda_date")[0].style.border = "3px solid red";
        document.getElementsByClassName("nepravda_date")[1].style.border = "3px solid red";
        document.getElementsByClassName("small_datum")[0].style.display = "block";
        return 0;
    }
}
function text_meno(){
    let meno = document.getElementById("inputMeno");
    if(meno.value.length === 0){
        document.getElementById("inputMeno").style.border = "3px solid red";
    }
    else{
        document.getElementById("inputMeno").style.border = "3px solid green";
    }
}
function text_priezvisko(){
    let priezvisko = document.getElementById("inputPriezvisko");
    if(priezvisko.value.length === 0){
        document.getElementById("inputPriezvisko").style.border = "3px solid red";
    }
    else{
        document.getElementById("inputPriezvisko").style.border = "3px solid green";
    }
}
function text_mail(){
    let mail  = document.getElementById("inputEmail");
    if(mail.value.length === 0){
        document.getElementById("inputEmail").style.border = "3px solid red";
    }
}
function text_datum(){
    let datum  = document.getElementById("inputDatum");
    if(datum.value.length === 0){
        document.getElementById("inputDatum").style.border = "3px solid red";
    }
}
function text_vek(){
    let vek  = document.getElementById("inputVek");
    if(vek.value.length === 0){
        document.getElementById("inputVek").style.border = "3px solid red";
    }
}
function teext(){
    return 1;
}
var stateObject = {
    "Protein": {
        "WEIDER Protein": ["WEIDER soy", "WEIDER Premium","WEIDER Casein"],
        "SCITEC NUTRITION Whey Protein": ["SCITEC NUTRITION Whey", "SCITEC NUTRITION soy","SCITEC NUTRITION Casein"],
        "BIOTECH USA Protein": ["BioTech USA whey","BioTech USA Micellar casein","BioTech USA Zero"]
    },
    "BCAA": {
        "Tabletkove": ["PVL Mutant BCAA Caps", "Vitalmax BCAA","EXTRIFIT BCAA"],
        "Praskove": ["WEIDER Premium BCAA", "SCITEC NUTRITION BCAA","NUTREND BCAA"],
        "Tekute": ["Nutrend BCAA Liquid", "NOCCO BCAA ","Extrifit BCAA"]
    },
    "Creatine": {
        "WEIDER": ["Pure Creatine", "Krea-Genic","Creatine HCL"],
        "SCITEC NUTRITION": ["King Creatine", "Trans-x Professional","Protected Creatine Concentrate"],
        "NUTREND": ["Kre-Alkalyne", "Monohydrate","Creapure"]
    }
}
window.onload = function () {
    let inputState1 = document.getElementById("inputState1"),
        inputState2 = document.getElementById("inputState2"),
        inputState3 = document.getElementById("inputState3");
    for (let state in stateObject) {
        inputState1.options[inputState1.options.length] = new Option(state, state);
    }
    inputState1.onchange = function () {
        inputState2.length = 1;
        inputState3.length = 1;
        if (this.selectedIndex < 1) {
            inputState2.options[0].text = "Prosím vyber si suplement"
            inputState3.options[0].text = "Prosím vyber si značku"
            return;
        }
        inputState2.options[0].text = "Vyber si aký druh"
        for (let druh in stateObject[this.value]) {
            inputState2.options[inputState2.options.length] = new Option(druh, druh);
        }
        if (inputState2.options.length==2) {
            inputState2.selectedIndex=1;
            inputState2.onchange();
        }

    }
    inputState1.onchange();
    inputState2.onchange = function () {
        inputState3.length = 1;
        if (this.selectedIndex < 1) {
            inputState3.options[0].text = "Vyber si suplement"
            return; // done
        }
        inputState3.options[0].text = "Vyber si presnejšie o aký druh ide"

        let presDruh = stateObject[inputState1.value][this.value];
        for (let i = 0; i < presDruh.length; i++) {
            inputState3.options[inputState3.options.length] = new Option(presDruh[i], presDruh[i]);
        }
        if (inputState3.options.length==2) {
            inputState3.selectedIndex=1;
            inputState3.onchange();
        }

    }
}
function check(){
    let meno = document.getElementById("inputMeno");
    let priezvisko = document.getElementById("inputPriezvisko");
    let datumm = document.getElementById("inputDatum");
    let vek = document.getElementById("inputVek");
    let mail = document.getElementById("inputEmail");

    if(datumm.value.length === 0){
        document.getElementsByClassName("button_small")[0].style.display = "block";
        document.getElementById("button").type = "button";
    }
    else if(meno.value.length === 0){
        document.getElementsByClassName("button_small")[0].style.display = "block";
        document.getElementsByClassName("pravda_meno")[0].style.border = "3px solid red";
        document.getElementById("button").type = "button";

    }
    else if(priezvisko.value.length === 0){
        document.getElementsByClassName("button_small")[0].style.display = "block";
        document.getElementsByClassName("pravda_priezvisko")[0].style.border = "3px solid red";
        document.getElementById("button").type = "button";
    }
    else if(vek.value.length === 0){
        document.getElementsByClassName("button_small")[0].style.display = "block";
        document.getElementsByClassName("nepravda_vek")[0].style.border = "3px solid red";
        document.getElementById("button").type = "button";
    }
    else if(mail.value.length === 0){
        document.getElementsByClassName("button_small")[0].style.display = "block";
        document.getElementsByClassName("nepravda_datum")[0].style.border = "3px solid red";
        document.getElementById("button").type = "button";
    }
    else{
        if(datum() === 1 && validEmail() === 1 ){
            document.getElementsByClassName("button_small")[0].style.display = "none";
            document.getElementById("button").type = "submit";
        }
        else{
            document.getElementsByClassName("button_small")[0].style.display = "block";
            document.getElementById("button").type = "button";
        }
    }
}