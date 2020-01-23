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
            this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-success'], 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-default'], 'Close'));
        } else {//ja ir visas 3 pogas
            this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-success'], 'Save'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-danger'], 'Delete'));
            this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-default'], 'Close'));
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
        this.formCount = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT').length;
        this.inputElem = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT');
        this.inputFail = false;//Seko līdzi tam vai lietotājs ir pareizi ievadījis datus

        // Šī daļa atbild par ievadīto datu nosūtīšanu uz serveri
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
                    if (
                        checkInput(this.inputElem[0].value) &&
                        checkInput(this.inputElem[1].value, 'number') &&
                        checkInput(this.inputElem[2].value, 'number') &&
                        checkInput([this.inputElem[1].value, this.inputElem[2].value], 'number')
                    ) {//Izveido jaunu grupu pogu
                        createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'color':
                    if (colorCount == colorLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                        alert('You have already saved ' + colorLimit + ' colors');
                    } else if (checkInput(this.inputElem[0].value)) {
                        this.createColorButt = new ColorBlock(this.inputElem[0].value, userRgbw, 'colorBlock', editColorButton);
                        document.getElementById('colorBlockContent').appendChild(this.createColorButt.build());
                        this.createColorButt.grow(document.getElementById('colorBlockContent').offsetWidth - this.createColorButt.blockWidth());
                        colorCount++;
                    } else {
                        this.inputFail = true;
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
                    if (
                        checkInput(this.inputElem[0].value) &&
                        checkInput(this.inputElem[1].value, 'number') &&
                        checkInput(this.inputElem[2].value, 'number') &&
                        checkInput([this.inputElem[1].value, this.inputElem[2].value], 'number')
                    ) {//Izveido jaunu grupu pogu
                        createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'updateColor'://apdeito krāsu pogu
                    if (checkInput(this.inputElem[0].value)) {
                        this.thisObj.updateData(this.inputElem[0].value);
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'updateAnimation'://apdeito animāciju pogu
                    if (checkInput(this.inputElem[0].value) &&
                        checkInput(this.inputElem[0].value, 'number'))
                        this.thisObj.updateData(this.inputElem[0].value, this.inputElem[1].value);
                    break;
            }
        }
        if (!this.inputFail) {
            ajaxConsoleSend(this.saveName + ' ' + this.saveValue);//nosūta datus uz serveri
        } else {
            // debugger;
            document.getElementsByClassName('popUpForm')[this.classIndex].reset();//reseto formu        
            // this.save();
        }
        document.getElementsByClassName('popUpForm')[this.classIndex].reset();//reseto formu        
    }

    closeSettings() {//noslēpj settings logu
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
        // console.log('close');
    }

    delete() {//izdzēš atbilstošo vērtību un elementu un nosūta dzēšamos datus uz serveri
        this.thisElement.remove();//izdzēš objektu iestatot tā vērtību uz 0
        if (this.thisElement.className == 'lampButton lampGroup') {
            currentLampString = '1-25#';
            checkButtHolders();//Atbilstoši pabīda pogas un saliek tās savās vietās
            riseGroupButts();  //Piešķir pārvietotajām pogām nepieciešamos izmērus
            ajaxConsoleSend('_delete_group_ ' + this.thisObj.getData()[0] + ' ' + this.thisObj.getData()[1] + ' ');
        } else if (this.thisElement.className == 'colorBlock') {
            growColors();
            ajaxConsoleSend('_delete_color_ ' + this.thisObj.getData()[0] + ' ' + stringColorSet(this.thisObj.getData()[1].slice(0, 4)) + ' ');
        } else if (this.thisElement.className == 'animBlock') {
            console.log('ANIMTEST: ',  );
            ajaxConsoleSend('_delete_anim_ ' + this.thisObj.getData()[0] + ' ' + stringFunctionSet(this.thisObj.getData()[1][0], this.thisObj.getData()[1][1]) + ' ');
        }
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
    }
}

function growColors() {//pēc krāsu pogas izdzēšanas palielina visas pārējās krāsu pogas, lai tās atbilstoši aizpildītu tukšo laukumu
    var place = document.getElementById('colorBlockContent');
    // console.log(place);
    var placeWidth = place.clientWidth;
    // console.log('PLACEWIDTH: ', placeWidth)
    var buttonWidth = 0;
    for (var i = 0; i < place.childElementCount; i++) {
        buttonWidth += place.getElementsByClassName('colorBlock')[i].offsetWidth + 5;
        // console.log('element: ', place.getElementsByClassName('colorBlock')[i]);
        // console.log('DIFFERENCE: ', placeWidth - buttonWidth);
        if (placeWidth - buttonWidth <= 2 && placeWidth - buttonWidth >= 0) {
            buttonWidth = 0;
            // console.log('C');
        } else if (placeWidth - buttonWidth < 0 && i != place.childElementCount - 1) {
            // console.log('A');
            place.getElementsByClassName('colorBlock')[i - 1].style.width = place.getElementsByClassName('colorBlock')[i - 1].offsetWidth + placeWidth - (buttonWidth - place.getElementsByClassName('colorBlock')[i].offsetWidth) + 5 + 'px';
            buttonWidth = place.getElementsByClassName('colorBlock')[i].offsetWidth + 5;
        } else if (i == place.childElementCount - 1 && placeWidth - buttonWidth > 1) {//Ja pēdējais elements
            // console.log('B', place.getElementsByClassName('colorBlock')[i]);
            // console.log(buttonWidth);
            // console.log(placeWidth);
            place.getElementsByClassName('colorBlock')[i].style.width = place.getElementsByClassName('colorBlock')[i].offsetWidth + placeWidth - buttonWidth + 'px';
        }
    }
}