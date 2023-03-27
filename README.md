# SETTING UP CREDENTIALS #
Add a new entry in your credential manager of windows. 

![](http://i.imgur.com/6NiMaFL.png)

Select Windows Credentials and add a new *generic* credential:

![](http://i.imgur.com/rhtgL1U.png)

# USE MODULE #
```
const credman = require('@stoneagebr/windows-credman');

const credential = credman.getCredentials("yourlabel");

console.log(credential);
```
