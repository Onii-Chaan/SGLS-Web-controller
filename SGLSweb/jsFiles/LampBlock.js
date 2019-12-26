class LampBlock{
    constructor(name, value){
        this.name = name;//lampas pogas nosaukums
        this.value = value;//lampas pogas vērtība
    }

    build(){
        this.colorBlock = document.createElement('DIV');

        this.colorBlock.innerHTML += this.name;//izveido nosaukuma paragrāfu
        this.colorBlock.setAttribute('name', this.value);//lai varētu vēlāk iegūt funkciju vērtības no elementa name

        this.colorBlock.classList.add('lampButton');
        this.colorBlock.addEventListener('click', function () {
            currentLamp = this.getAttribute('name');//iegūst esošo nospiesto lampas vērtību
        });
        return this.colorBlock;
    }
}

