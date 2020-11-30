
const container = popmotion.styler(document.querySelector('.container'))
const formElements = (document.querySelector('.inner'))
const msgPop = popmotion.styler(document.querySelector('.msg'))
//pristup k elementom ktore chceme animovat
//popmotion sluzi na referencovanie vselijakych specifickych metod
//querySelector je cisty DzavaSkript sluzi na vybratie klasy
popmotion.tween({            //otvorime si objekt
    from:{                      //otvorime si  dalsi objekt
        scale:.7,               //znamena ze zacne 0.7 co je vlastne 70%
        opacity:0,              // velkost z jeho default velkosti
        y:-300
    },
    to:{
        scale: 1,
        opacity: 1,
        y:0
    },
    duration: 1000
}).start(container.set)    //container je referencia na container co sme
// si vytvorili hore a .set prakticky znamena ze
// setne tie vlasnosti do toho containera ktory sa bude animovat


