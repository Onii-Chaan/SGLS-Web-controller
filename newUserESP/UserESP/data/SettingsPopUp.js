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
                this.popElement.appendChild(buildElementNode('P', 'settingsText', this.inputFields[i][0]));
                this.createInput = buildElementNode('INPUT', this.inputFields[i][1]);
                this.createInput.classList.add('popUpInput');
                this.popElement.appendChild(this.createInput);
            } else {
                this.popElement.appendChild(buildElementNode('P', 'settingsText', this.inputFields[i][0]));
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

        if (this.inputElem.length >= 2 && this.createType != 'updateAnimation') {
            this.userInputData = [parseInt(this.inputElem[1].value), parseInt(this.inputElem[2].value)];
        } else if (this.createType == 'updateAnimation') {
            this.userInputData = [parseInt(this.inputElem[1].value)];
        }

        if (this.createType != '') {//ja dotajam settings logam ir jāizveido vēl kāds jauns elements
            switch (this.createType) {
                case 'group':
                    if (
                        checkInput(this.inputElem[0].value) &&
                        checkInput(this.inputElem[1].value, 'number') &&
                        checkInput(this.userInputData, 'number') &&
                        checkInput(this.inputElem[2].value, 'number')
                    ) {//Izveido jaunu grupu pogu
                        if (groupCount == savedLimit) {
                            alert('You have already saved ' + savedLimit + ' groups');
                        } else {
                            ajaxConsoleSend('/addgroup/' +//nosūta datus uz konsoli
                                urlQuery(
                                    createDic(
                                        [
                                            "name",
                                            "value"
                                        ],
                                        [
                                            this.inputElem[0].value,
                                            createGroupString(this.inputElem[1].value, this.inputElem[2].value)
                                        ]
                                    )
                                )
                            );
                            createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                            groupCount++;                        
                        }
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'color':
                    if (colorCount == savedLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                        alert('You have already saved ' + savedLimit + ' colors');
                    } else if (checkInput(this.inputElem[0].value)) {
                        ajaxConsoleSend(//nosūta jaunās izveidotās krāsas vērtību
                            '/addcolor/' +
                            urlQuery(
                                createDic(
                                    ['name', 'r', 'g', 'b', 'w'],
                                    [this.inputElem[0].value].concat(userRgbw)
                                )
                            )
                        );
                        rgbwArr.push([this.inputElem[0].value].concat(userRgbw));//iepušo lietotāja ievadīto vērtību globālajā masīvā
                        this.deletedData = userRgbw;//izveido masīvu nosūtīšanai
                        this.deletedData.push(this.inputElem[0].value)
                        growColors(this.deletedData, false);//pievieno jauno krāsu
                        colorCount++;
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'animation':
                    break;
                case 'add':
                    if (this.dataIn[3]) {//ja ir jāizveido jauns krāsu bloks
                        if (colorCount == savedLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                            alert('You have already saved ' + savedLimit + ' colors');
                        } else {
                            ajaxConsoleSend(//nosūta jaunās izveidotās krāsas vērtību
                                '/addcolor/' +
                                urlQuery(
                                    createDic(
                                        ['name', 'r', 'g', 'b', 'w'],
                                        [this.dataIn[4]].concat(this.dataIn.slice(0, 4))
                                    )
                                )
                            );
                            /*Izveido jauno krāsu pogu*/
                            rgbwArr.push([this.dataIn[4]].concat(this.dataIn.slice(0, 4)));//iepušo lietotāja ievadīto vērtību globālajā masīvā
                            this.deletedData = this.dataIn.slice(0, 4);//izveido masīvu nosūtīšanai
                            this.deletedData.push(this.dataIn[4])
                            growColors(this.deletedData, false);//pievieno jauno krāsu
                            colorCount++;
                        }
                    } else {
                        if (animCount == savedLimit) {
                            alert('You have already saved ' + savedLimit + ' animations');
                        } else {
                            // console.log(this.dataIn.slice(0, 2));
                            ajaxConsoleSend(//nosūta jaunās pievienotās animāciju pogas parametrus
                                '/addanim/' +
                                urlQuery(
                                    createDic(
                                        [
                                            "name",
                                            "funcNum",
                                            "param"
                                        ],
                                        [
                                            this.dataIn[4],
                                            this.dataIn[0],
                                            this.dataIn[1]
                                        ]
                                    )
                                )
                            );
                            this.createColorButt = new AnimationsBlock(this.dataIn[4], this.dataIn.slice(0, 2), 'animBlock', editAnimButton);
                            document.getElementById('animBlockContent').appendChild(this.createColorButt.buildAnimBlock());
                            funcArr.push([this.dataIn[4], this.dataIn[0], this.dataIn[1]]);
                            animCount++;
                        }
                        // else if(){} !!!!! JĀIZVEIDO ADD DAĻU PRIEKŠ GRUPU POGĀM
                    }
                    break;
                case 'updateGroup'://apdeito grupu pogu
                    if (
                        checkInput(this.inputElem[0].value) &&
                        checkInput(this.inputElem[1].value, 'number') &&
                        checkInput(this.inputElem[2].value, 'number') &&
                        checkInput([this.inputElem[1].value, this.inputElem[2].value], 'number')
                    ) {//apdeito grupu pogu
                        this.funcIdToDel = findArrIndex(//atrod grupu indeksu masīvā
                            lampGroups,
                            [this.thisObj.getData()[0], this.thisObj.getData()[1]]
                        );
                        this.thisObj.updateData(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value));
                        ajaxConsoleSend(//apdeito krāsas datus
                            '/updategroup/' +
                            urlQuery(
                                createDic(
                                    ['name', 'value', 'index'],
                                    [
                                        this.thisObj.getData()[0],
                                        this.thisObj.getData()[1],
                                        this.funcIdToDel
                                    ]
                                )
                            )
                        );
                        lampGroups[this.funcIdToDel] = [//iestata jaunās vērtības grupu masīvā
                            this.thisObj.getData()[0],
                            this.thisObj.getData()[1]
                        ]
                        // createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'updateColor'://apdeito krāsu pogu
                    if (checkInput(this.inputElem[0].value)) {
                        this.changeIndex;
                        for (var i = 0; i < rgbwArr.length; i++) {
                            if (rgbwArr[i].indexOf(this.thisObj.getData()[0]) != - 1) {
                                rgbwArr[i][0] = this.inputElem[0].value;
                                this.changeIndex = i;
                                break;
                            }
                        }
                        this.thisObj.updateData(this.inputElem[0].value);

                        this.updateArr = [...this.thisObj.getData()[1]];//izveido un pārveido masīvu priekš datu nosūtīšanas uz serveri
                        this.updateArr.push(this.thisObj.getData()[0]);
                        this.updateArr = bringLastToFirst(this.updateArr);
                        this.updateArr.push(this.changeIndex);

                        ajaxConsoleSend(//apdeito krāsas datus
                            '/editcolor/' +
                            urlQuery(
                                createDic(
                                    ['name', 'r', 'g', 'b', 'w', 'index'],
                                    this.updateArr
                                )
                            )
                        );


                    } else {
                        this.inputFail = true;
                    }
                    break;
                case 'updateAnimation'://apdeito animāciju pogu
                    this.funcIdToDel = findArrIndex(//atrod animācijas indeksu masīvā
                        funcArr,
                        [this.thisObj.getData()[0]].concat(this.thisObj.getData()[1])
                    );

                    if (this.inputElem[0].value != '' && checkInput(this.inputElem[0].value)) {//iestata jaunās ievadītās vērtības
                        this.thisObj.updateData(this.inputElem[0].value);
                    }
                    if (this.inputElem[1].value != '' &&//iestata jaunās ievadītās vērtības
                        checkInput(this.inputElem[1].value, 'number')) {
                        this.thisObj.updateData('', this.inputElem[1].value);
                    }

                    ajaxConsoleSend(
                        '/editanim/' +
                        urlQuery(
                            createDic(
                                [
                                    "name",
                                    "funcNum",
                                    "param",
                                    "index"
                                ],
                                [
                                    this.thisObj.getData()[0],
                                    this.thisObj.getData()[1][0],
                                    this.thisObj.getData()[1][1],
                                    this.funcIdToDel
                                ]
                            )
                        )
                    );
                    funcArr[this.funcIdToDel] = [//iestata jaunās vērtības funkciju masīvā
                        this.thisObj.getData()[0],
                        this.thisObj.getData()[1][0],
                        this.thisObj.getData()[1][1]
                    ]
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
    }

    delete() {//izdzēš atbilstošo vērtību un elementu un nosūta dzēšamos datus uz serveri
        this.thisElement.remove();//izdzēš objektu iestatot tā vērtību uz 0
        if (this.thisElement.className == 'ellipsisText lampButton lampGroup') {
            currentLampString = '1-' + lampNum + '#';

            this.funcIdToDel = findArrIndex(//atrod animācijas indeksu masīvā
                lampGroups,
                this.thisObj.getData()
            );
            checkButtHolders();//Atbilstoši pabīda pogas un saliek tās savās vietās
            riseGroupButts();  //Piešķir pārvietotajām pogām nepieciešamos izmērus
            ajaxConsoleSend('/deletegroup/' +//nosūta datus uz konsoli
                urlQuery(
                    createDic(
                        [
                            "name",
                            "value",
                            "index"
                        ],
                        [
                            this.thisObj.getData()[0],
                            this.thisObj.getData()[1],
                            this.funcIdToDel
                        ]
                    )
                )
            );
            lampGroups.splice(this.funcIdToDel, 1);//izdzēš grupu no masīva
            groupCount--;
        } else if (this.thisElement.className == 'ellipsisText colorBlock') {
            this.growArr = [...this.thisObj.colorValue];//izveido nosūtāmo masīvu uz growColors
            this.growArr.push(this.thisObj.colorName)
            growColors(this.growArr);//izveido jaunos krāsu blokus
            colorCount--;
        } else if (this.thisElement.className == 'animBlock ellipsisText') {
            this.funcIdToDel = findArrIndex(//atrod animācijas indeksu masīvā
                funcArr,
                [this.thisObj.getData()[0]].concat(this.thisObj.getData()[1])
            );
            console.log([this.thisObj.getData()[0]].concat(this.thisObj.getData()[1]));
            ajaxConsoleSend(
                '/deleteanim/' +
                urlQuery(
                    createDic(
                        [
                            "name",
                            "funcNum",
                            "param",
                            "index"
                        ],
                        [
                            this.thisObj.getData()[0],
                            this.thisObj.getData()[1][0],
                            this.thisObj.getData()[1][1],
                            this.funcIdToDel
                        ]
                    )
                )
            );
            funcArr.splice(this.funcIdToDel, 1);//izdzēš funkciju no masīva
            animCount--;
        }
        backShadow(false);//iestata fona ēnu
        document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
    }
}

function growColors(deletedData, toDelete = true) {//pēc krāsu pogas izdzēšanas palielina visas pārējās krāsu pogas, lai tās atbilstoši aizpildītu tukšo laukumu
    deletedData = bringLastToFirst(deletedData);//pārvieto pēdējo element (nosaukumu) uz nulto pozīciju
    if (toDelete) {
        let arrIndex = findArrIndex(rgbwArr, deletedData);
        deletedData.push(arrIndex);//izveido masīvu ar visu indeksu
        ajaxConsoleSend(
            '/deletecolor/' +
            urlQuery(
                createDic(
                    ['name', 'r', 'g', 'b', 'w', 'index'],
                    deletedData
                )
            )
        );
        rgbwArr.splice(arrIndex, 1);
    }

    let placeHolder = document.getElementById('colorBlockContent');//izdzēš visas krāsu pogas
    while (placeHolder.firstChild) {
        placeHolder.removeChild(placeHolder.firstChild);
    }

    blockWidthCount = 0;
    colorBlockObjArr = [];
    let arrLen = rgbwArr.length;
    for (let i = 0; i < arrLen; i++) {
        //izveido krāsu pogas un saliek tās collapsible pogas kontentā
        colorBlockObjArr.push(
            new ColorBlock(
                rgbwArr[i][0],
                rgbwArr[i].slice(1, 5),
                'colorBlock',
                editColorButton)
        );
        addColorBlock(i, COLOR_COLLAPSIBLE_OBJ, colorBlockObjArr, arrLen, true);//!!!!!
    }
}

