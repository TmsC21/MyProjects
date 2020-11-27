let titleList = [];
let i = 0;
let dragElement;
let hoverElement;
let order = [0,1,2,3,4,5];
document.addEventListener("DOMContentLoaded",()=>{
    let o =0;
    let galleryWrapper = document.getElementById("gallery_wrapper");
    let input_text = document.getElementById("Input_text");
    let sliderImage = document.getElementById("gallery_slider_block");
    let inpGetKokie = getCookie("inp");
    let orderGetKokie = getCookie("order");
    if(inpGetKokie){
        input_text.value = inpGetKokie;
        inp_text(input_text.value);
    }
    if(orderGetKokie){
       order = JSON.parse(orderGetKokie);
    }
    fetch("photos.json")
        .then(response => response.json())
        .then(json =>{
            order.forEach((item,index)=>{
                titleList.push(json.photos[item].title);
                let galleryItem = document.createElement("img");
                galleryItem.setAttribute("src", "images/"+json.photos[item].src);
                galleryItem.id = item;
                galleryItem.title = titleList[i++];
                galleryItem.classList = "tump";
                galleryWrapper.appendChild(galleryItem);

                galleryItem.ondragstart = (evt)=>{
                    dragElement = evt.target;
                };
                galleryItem.ondragover = (evt)=>{
                    hoverElement = evt.target;
                    galleryWrapper.insertBefore(dragElement,hoverElement.nextSibling);
                    for (let x = 0; x<galleryWrapper.childElementCount;x++){
                        order[x] = galleryWrapper.children[x].id;
                        setCookie("order",JSON.stringify(order),1)
                    }
                    for (let x = 0; x<galleryWrapper.childElementCount;x++){
                        if(galleryWrapper.children[x].id === galleryItem.id){
                            o = x;
                        }
                    }
                };

                galleryItem.onclick=(evt)=>{

                    sliderImage.style.backgroundImage = "url("+galleryItem.src+")";
                    openSlider();
                    let prev = document.getElementById("prev").title;
                    let next = document.getElementById("next").title;
                    for (let x = 0; x<galleryWrapper.childElementCount;x++){
                        if(galleryWrapper.children[x].id === galleryItem.id){
                            o = x;
                        }
                    }

                };

            })
            document.getElementById("next").addEventListener("click",()=>{
                o++;
                if(o > 5){
                    o=0;
                }
                sliderImage.style.backgroundImage = "url("+galleryWrapper.children[o].src+")";
            })
            document.getElementById("prev").addEventListener("click",()=>{
                o--;
                if(o < 0){
                    o=5;
                }
                sliderImage.style.backgroundImage = "url("+galleryWrapper.children[o].src+")"
            })
            function fnc(){
                o++;
                if(o > 5){
                    o=0;
                }
                sliderImage.style.backgroundImage = "url("+galleryWrapper.children[o].src+")"
            }
            var inter;
            document.getElementById("play").addEventListener("click",()=>{
                inter = setInterval(fnc,1500);

            })
            document.getElementById("stop").addEventListener("click",()=>{
                clearInterval(inter);
            })
            input_text.addEventListener("input",inp_text)
            inp_text(input_text);
        })
    function inp_text(evt){
        for (let x = 0; x<galleryWrapper.childElementCount;x++){
            galleryWrapper.children[x].style.display = "none";
        }
        titleList.map(function(algo){
            input_text.value.split(" ").map(function (word){
                if(algo.toLowerCase().indexOf(word.toLowerCase()) != -1){
                    for (let x = 0; x<galleryWrapper.childElementCount;x++){
                        if(algo == galleryWrapper.children[x].title){
                            galleryWrapper.children[x].style.display = "";
                        }
                    }
                }
            })
        })
        setCookie("inp",input_text.value,1);
        let or = document.getElementById("obr");
    }

})
function setCookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires="+ d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}
function getCookie(cname) {
    var name = cname + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for(var i = 0; i <ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}
function closeSlider(){
    document.getElementById("gallery_slider").style.display = "none";
}
function openSlider(){
    document.getElementById("gallery_slider").style.display = "flex";
}
