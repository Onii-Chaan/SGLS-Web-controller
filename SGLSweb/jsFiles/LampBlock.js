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
        if (this.options != '') {
            this.colorBlock.classList.add('lampGroup');//lai būtu atšķirība no parastājām lampu pogām
        }


        this.colorBlock.onclick = methodize(this.sendButtonValue, this);//pievieno klikšķa iespēju
        // console.log('a', placeToBuild);
        if (typeof placeToBuild == 'number') {//izvēlās, kurā vietā tiks būvēta nākamā lampu poga
            // console.log('placeToBuild: '+ placeToBuild);
            document.getElementsByClassName('groupButtonHolder')[placeToBuild].appendChild(this.colorBlock);
        } 
        // else {
        //     console.log('parentNode: ');
        //     document.getElementsByClassName('groupButtonHolder')[parseInt(placeToBuild.substring(3,4))].parentNode.insertBefore(this.colorBlock, placeToBuild.nextSibling);//uzbūvē grupas pogu pēc pēdējās grupas pogas
        // }

        if (this.options != '') {//pievieno dubultklikšķa iespēju
            this.colorBlock.ondblclick = methodize(this.doubleClick, this);
        }
    }

    doubleClick() {
        this.options.open('', this.colorBlock, this);
    }

    sendButtonValue() {
        currentLampString = this.value;
        document.getElementById('displayCurrentLamp').innerHTML = this.value;
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

