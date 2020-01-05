class AnimationsBlock extends ColorBlock {//animāciju bloks ir tāds pats kā ColorBlock, bet ar citiem parametriem
    buildAnimBlock() {
        this.colorBlock = document.createElement('DIV');

        this.colorBlock.innerHTML += this.colorName;//izveido nosaukuma paragrāfu

        this.colorBlock.classList.add('animBlock');

        this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + this.colorValue[1]);//lai varētu vēlāk iegūt funkciju vērtības no elementa name


        this.colorBlock.onclick = methodize(this.click, this);
        return this.colorBlock;
    }

    click() {
        this.findMatch = this.colorBlock.getAttribute('name').match(/\d+/g);//atrod iekš name esošos parametrus funkcijai
        sendValue(1, '1-42', stringFunctionSet(this.findMatch[0], this.findMatch[1]));
    }
}
