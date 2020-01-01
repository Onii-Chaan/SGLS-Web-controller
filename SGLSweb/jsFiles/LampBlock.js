class LampBlock{
    constructor(name, value, options = ''){
        this.name = name;//lampas pogas nosaukums
        this.value = value;//lampas pogas vērtība
        
        this.options = options;
        // console.log(this.options);
        if(this.options!=''){
            console.log('OptionsTest: ', this.options);
            this.options.build();
            this.options.close();
        }
    }

    build(){
        this.colorBlock = document.createElement('DIV');

        this.colorBlock.innerHTML += this.name;//izveido nosaukuma paragrāfu
        this.colorBlock.setAttribute('name', this.value);//lai varētu vēlāk iegūt funkciju vērtības no elementa name
        this.colorBlock.classList.add('lampButton');

        
        // this.colorBlock.addEventListener('dblclick', function () {
            // console.log('doubleClick');
            // currentLamp = this.getAttribute('name');//iegūst esošo nospiesto lampas vērtību
            // console.log('CurrentLampValue', currentLamp);
        // });
        // this.colorBlock.addEventListener('click', function () {
            // currentLamp = this.getAttribute('name');//iegūst esošo nospiesto lampas vērtību
            // console.log('CurrentLampValue', currentLamp);
        // });

        document.body.appendChild(this.colorBlock);
        
        this.colorBlock.ondblclick = this.doubleClick;
    }

    doubleClick(){
        console.log('What is this?', this);
        this.options.open();
    }

    openOption(){
        this.colorBlock = document.createElement('DIV');

        this.colorBlock.innerHTML += this.name;//izveido nosaukuma paragrāfu
        this.colorBlock.setAttribute('name', this.value);//lai varētu vēlāk iegūt funkciju vērtības no elementa name

        this.colorBlock.classList.add('lampButton');
        this.colorBlock.addEventListener('click', function () {
            currentLamp = this.getAttribute('name');//iegūst esošo nospiesto lampas vērtību
            console.log('OpenSettings');
        });
        return this.colorBlock;
    }
}   

