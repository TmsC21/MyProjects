const container = popmotion.styler(document.querySelector('.container'))
const formElements = (document.querySelector('.inner'))
const msgPop = popmotion.styler(document.querySelector('.msg'))
//pristup k elementom ktore chceme animovat
//popmotion sluzi na referencovanie vselijakych specifickych metod
//querySelector je cisty DzavaSkript sluzi na vybratie klasy
const myAnim = popmotion.tween({                                      //otvorime si objekt
    from:{                                                              //otvorime si  dalsi objekt
        scale:.7,            //znamena ze zacne 0.7 co je vlastne 70% velkost z jeho default velkosti
        opacity:0,
        y:-300
    },
    to:{
        scale: 1,
        opacity: 1,
        y:0
    },
    duration: 1000
})//.start(container.set)    //container je referencia na container co sme
// si vytvorili hore a .set prakticky znamena ze
// setne tie vlasnosti do toho containera ktory sa bude animovat

const myAnim2 = popmotion.keyframes({
    values:[                //valeus je vlastne pole do ktoreho zadame objekty(keyframy)
        {y: -50,opacity:0},
        {y: -20,opacity:1},
        {y: -20,opacity:1},
        {y: -0,opacity:0},
    ],
    times:[0,.2,.8,1],      //tymto mozeme urcit timing ako dlho dokaze ostat v urcitich keyframoch
    duration: 1000
})

myAnim.start({
    update: container.set,                  //je vlastne to iste ako by sme dali .start(container.set)
    complete:()=>{myAnim2.start(msgPop.set)}//do complete hodime funkciu ktora nam po
                                            // dokonceni prvej animacie spusti druhu
});
const stylers = Array.from(formElements.children).map(popmotion.styler)
//vytvorenie pola z formElements(vsetko v co je v inner class)

const animations = Array(stylers.length).fill(popmotion.spring({from: 100,to: 0}))
//A potom definujeme animaciu cez cele pole pouzitim fill a v tomto pripade vytvorime spring animaciu z 100 do 0

popmotion.stagger(animations,100).start((v)=>v.forEach((x,i) => stylers[i].set('x',x)))
//potom pouzijeme stagger na prechadzanie animacii prvom argumente, druhy argument je delay
//stagger animacia zacina start metodou ktora iteruje cez animacie a potom berie hodnotu x
//a setuje ich na hodnotu from a to ako cez ich iteruje

