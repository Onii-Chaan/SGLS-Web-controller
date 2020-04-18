class Icon {//ikonas klase
    constructor(classType, iconSize) {
        this.classType = classType;
        this.iconSize = iconSize;

        this.iconDiv;
        this.arrHoldDiv;
    }

    buildArrow() {
        this.arrHoldDiv = document.createElement('DIV');
        this.iconDiv = document.createElement('DIV');

        this.iconDiv.classList.add(this.iconSize);
        this.arrHoldDiv.classList.add(this.classType);
        this.arrHoldDiv.classList.add(this.iconSize);

        this.iconDiv.appendChild(this.arrHoldDiv);
        return this.iconDiv;
    }
}
