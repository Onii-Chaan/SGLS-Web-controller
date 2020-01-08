class SettingsPopUp {//pop elementu klase
    constructor(title, inputFields, buttonCount, type, classIndex, createType = '') {
        this.title = title;//popapa virsraksts
        this.inputFields = inputFields;//visu ievades lauciņu raksturojumi
        this.buttonCount = buttonCount;//Pogu daudzums

        this.popUp;//PopUp elementa galvenais div
        this.data;//saglabā lietotāja ievadītos input datus

        this.type = type;//nosaka vai šī ir grupas, animācijas, vai krāsu poga, STĀV NEIZMANTOTS

        this.classIndex = classIndex;//nepieciešams, lai manipulētu ar vairākiem settingu elementiem
        this.createType = createType;//ja ir jāizveido kādus jaunus elementus, tad nosaka to tipu

        this.dataIn;//klases globālais mainīgais, lai varētu apstrādāt ienākošos datus
        this.thisElement;//tiek padots objekta HTML elements, caur kuru arī atvēra settings 
        this.thisObj;//tiek saglabāts esošais objekts, caur kuru tika atvērts settings
    }

    build() {
        this.popUp = buildElementNode('DIV', 'settingsPopUp');//izveido pop up divu
        this.popElement = buildElementNode('FORM', 'popUpForm');
        this.popUp.appendChild(buildElementNode('H3', 'settingsPopTitle', this.title));//izveido virsrakstu

        var inputCount = this.inputFields.length;
        for (var i = 0; i < inputCount; i++) {//izveido visus ievades lauciņus
            if (this.inputFields[i][1] != 'double') {
                this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
                this.createInput = buildElementNode('INPUT', this.inputFields[i][1]);
                this.createInput.classList.add('popUpInput');
                this.popElement.appendChild(this.createInput);
            } else {
                this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
            }
        }
        this.buttonHolder = buildElementNode('DIV', 'actionButtonsHolder');//izveido pogas divu
        if (this.buttonCount == 2) {
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Close'));
        } else {//ja ir visas 3 pogas
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Delete'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', 'actionButton', 'Close'));
        }

        this.popUp.appendChild(this.popElement);
        this.popUp.appendChild(this.buttonHolder);//pievieno pogas galvenajam divam
        this.popElement = document.body.appendChild(this.popUp);//pop up element, lai ar to varētu turpāk veikt manipulācijas


        if (this.buttonCount == 3) {
            this.popElement.getElementsByClassName('actionButton')[0].onclick = methodize(this.save, this);

            this.popElement.getElementsByClassName('actionButton')[1].onclick = methodize(this.delete, this);
            this.popElement.getElementsByClassName('actionButton')[2].onclick = methodize(this.closeSettings, this);
        } else {
            this.popElement.getElementsByClassName('actionButton')[0].onclick = methodize(this.save, this);
            this.popElement.getElementsByClassName('actionButton')[1].onclick = methodize(this.closeSettings, this);
        }
        document.getElementsByClassName('settingsPopUp')[0].style.display = 'none';
        backShadow(false);//iestata fona ēnu

    }

    open(dataIn = '', thisElement = '', thisObj) {//parāda settings logu
        this.dataIn = dataIn;
        this.thisElement = thisElement;
        this.thisObj = thisObj;
        backShadow(true);
        this.popUp.style.display = 'block';
    }

    save() {
        //nosūta uz serveri lietotāja jaunos ievadītos datus un izveido jaunus elementus, ja tas ir nepieciešams
        // this.dataIn = dataIn;//ja ir kkādi dati, kas ir papildus jāapstrādā saglabājot
        // console.log('thisDataIn:', this.dataIn);
        // console.log('dataIn: ', dataIn);
        this.formCount = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT').length;
        this.inputElem = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT');



        if (this.formCount > 0) {//ja ir bijusi viesmaz viena forma
            this.saveName = 'name=' + this.inputElem[0].value;//nolasa input datus un atbilstoši tos pārveido
            if (this.formCount < 3) {
                // this.saveValue = 'value=' + this.inputElem[1].value;
            } else if (this.formCount == 3) {
                this.saveValue = 'value=' + createGroupString(this.inputElem[1].value, this.inputElem[2].value);
            }
        }

        if (this.createType != '') {//ja dotajam settings logam ir jāizveido vēl kāds jauns elements
            switch (this.createType) {
                case 'group':
                    createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                    break;
                case 'color':
                        if (colorCount == colorLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                            alert('You have already saved ' + colorLimit + ' colors');
                        } else {
                            this.createColorButt = new ColorBlock(this.inputElem[0].value, userRgbw, 'colorBlock', editColorButton);
                            document.getElementById('colorBlockContent').appendChild(this.createColorButt.build());
                            this.createColorButt.grow();
                            colorCount++;
                        }
                    break;
                case 'animation':
                    break;
                case 'add':
                    if (this.dataIn.length == 5) {//ja ir jāizveido jauns krāsu bloks
                        if (colorCount == colorLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                            alert('You have already saved ' + colorLimit + ' colors');
                        } else {
                            this.createColorButt = new ColorBlock(this.dataIn[4], this.dataIn.slice(0, 4), 'colorBlock', editColorButton);
                            document.getElementById('colorBlockContent').appendChild(this.createColorButt.build());
                            this.createColorButt.grow();
                            colorCount++;
                        }
                    } else {
                        if (animCount == animLimit) {
                            alert('You have already saved ' + animLimit + ' animations');
                        } else {
                            // console.log(this.dataIn.slice(0, 2));
                            this.createColorButt = new AnimationsBlock(this.dataIn[2], this.dataIn.slice(0, 2), 'animBlock', editAnimButton);
                            document.getElementById('animBlockContent').appendChild(this.createColorButt.buildAnimBlock());
                            animCount++;
                        }
                    }
                    break;
                case 'updateGroup'://apdeito grupu pogu
                    this.thisObj.updateData(this.inputElem[0].value, [this.inputElem[1].value, this.inputElem[2].value]);//apdeuto group pogas datus
                    break;
                case 'updateColor'://apdeito krāsu pogu
                    this.thisObj.updateData(this.inputElem[0].value);
                    break;
                case 'updateAnimation'://apdeito animāciju pogu
                    this.thisObj.updateData(this.inputElem[0].value, this.inputElem[1].value);
                    break;
            }
        }

        ajaxConsoleSend(this.saveName + ' ' + this.saveValue);//nosūta datus uz serveri
        document.getElementsByClassName('popUpForm')[this.classIndex].reset();//reseto formu
        // console.log('save');
    }

    closeSettings() {//noslēpj settings logu
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
        // console.log('close');
    }

    delete() {//izdzēš atbilstošo vērtību un elementu
        // console.log(this.thisElement.className);
        this.thisElement.remove();//izdzēš objektu iestatot tā vērtību uz 0
        if(this.thisElement.className == 'lampButton lampGroup'){
            currentLampString = '1-25#';
            riseGroupButts();   
        }
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
    }

    returnData(dataToGet) {
        return;
    }
}