class LampBlock {
    constructor(name, value, options = '') {
        this.name = name;//lampas pogas nosaukums
        this.value = value;//lampas pogas vērtība
        if (typeof this.value == 'number') {
            this.value = createGroupString(this.value, this.value);
        }
        this.options = options;
        // console.log(this.options);
        // if (this.options != '') {
        // this.options.build();
        // console.log('nowClose');
        // this.options.closeSettings();
        // }
    }

    build(placeToBuild = '') {
        this.colorBlock = document.createElement('DIV');
        
  
        this.colorBlock.innerHTML = this.name;//izveido nosaukuma paragrāfu
        this.colorBlock.setAttribute('name', this.value);//lai varētu vēlāk iegūt funkciju vērtības no elementa name
        this.colorBlock.classList.add('lampButton');
        // this.colorBlock.classList.add('no_selection');
        if (this.options != '') {
            this.colorBlock.classList.add('lampGroup');//lai būtu atšķirība no parastājām lampu pogām
        }

        // console.log(this.colorBlock.style.backgroundColor);
        // this.textColor = parseToRGBA(this.colorBlock.style.background);
        // console.log(this.textColor);
        // this.colorBlock.style.color = getContrast(this.colorValue.slice(0,3));
        

        this.colorBlock.onclick = methodize(this.sendButtonValue, this);//pievieno klikšķa iespēju
        if (typeof placeToBuild == 'number') {//izvēlās, kurā vietā tiks būvēta nākamā lampu poga
            document.getElementsByClassName('groupButtonHolder')[placeToBuild].appendChild(this.colorBlock);
        } 

        if (this.options != '') {//pievieno dubultklikšķa iespēju
            this.colorBlock.ondblclick = methodize(this.doubleClick, this);
        }
    }

    doubleClick() {
        this.options.open('', this.colorBlock, this);
    }

    sendButtonValue() {
        currentLampString = this.value;
        document.getElementById('displayCurrentLamp').innerHTML = this.name;
        console.log('CurrentLampValue', this.value);
    }

    updateData(name = '', value = '') {//apdeito lampBlock elementu
        if (name != this.name && name != '' && typeof name != 'undefined') {//pārbauda vai var apdeitot vārdu
            this.colorBlock.innerHTML = name;
        } else if (createGroupString(value[0], value[1]) != this.value && !value.includes('') && !value.includes(undefined)) {//pārbauda vai var apdeitot vērtību
            console.log(value[1]);
            this.value = createGroupString(value[0], value[1]);
        }
    }
}
