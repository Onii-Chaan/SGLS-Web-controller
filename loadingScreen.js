

var loadingScreen = {
    // background: 'gray',
    start: function () {//parāda ielādēšanās elementus
        // console.log('execute');
        this.loadingElement = document.createElement('DIV');//izveido tumšo fonu
        this.loadingElement.classList.add('loadingDiv');
        this.loadingElement.style.background = this.background;


        this.loadingRoll = document.createElement('DIV');//izveido rotējošo elementu
        this.loadingRoll.classList.add('loader');

        this.loadingElement.appendChild(this.loadingRoll);//savieno kopā fonu ar rotējošo elementu 
        document.body.appendChild(this.loadingElement);//pievieno visu dokumentam
    },

    end: function () {//izbeidz ielādēšanās elementu darbību
        var fadeTarget = document.getElementsByClassName('loadingDiv')[0];
        var fadeEffect = setInterval(function () {
            if (!fadeTarget.style.opacity) {
                fadeTarget.style.opacity = 1;
            }
            if (fadeTarget.style.opacity > 0) {
                fadeTarget.style.opacity -= 0.1;
            } else {
                clearInterval(fadeEffect);
                fadeTarget.style.display = 'none';

            }
        }, 10);
    }
};

loadingScreen.start();//izveido ielādē lādēšanās ekrānu
// window.addEventListener('load', loadingScreen.end(), false);//aizver lādēšanās ekrānu
