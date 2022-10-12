#!/bin/bash
sso="JKLU"
#password="wifi@jklu21"

site="http://172.16.1.1:8090"

#curl -S "${site}/login.xml" -H "Content-Type: application/x-www-form-urlencoded" -d "mode=191&username=${username}&password=${password}&a=1664597185453&producttype=0"


#init funtion

init(){
    echo "WELCOME TO SHELL CONNECT"
    echo
    read -p "ENTER YOUR USERNAME : " username
    echo
    read -s -p "ENTERYOUR PASSWORD : " password
    echo

    touch ~/.conconfig

   a="$username:$password"
   echo $a > ~/.conconfig

}

#login function

login(){
    value=$(<~/.conconfig)

    OIFS=$IFS

    IFS=":"
    credentials=($value)
    IFS=$OIFS
   curl -S "${site}/login.xml" -H "Content-Type: application/x-www-form-urlencoded" -d "mode=191&username=${credentials[0]}&password=${credentials[1]}&a=1664597185453&producttype=0"
}

#logout function

lgout(){

    value=$(<~/.conconfig)

    OIFS=$IFS

    IFS=":"
    credentials=($value)

   curl -S "${site}/logout.xml" -H "Content-Type: application/x-www-form-urlencoded" -d "mode=193&username=${credentials[0]}&a=1665550636225&producttype=0"
    credentials=($value)
}
#switch case for command read
case $1 in
    "init" | "-i" )
        echo "Starting initialiser script..."
        echo
        init
        ;;
    "login" | "-l")
        echo "STARTING LOG IN..."
        echo
        login
        ;;
    "logout" | "-e")
        echo "Logging out"
        echo
        lgout
        ;;
    "--help" | "-h")
        echo "Description: A script that reduces time to login in JKLU wifi"
        echo
        echo "usage: cc [OPTION]"
        echo
        echo "-i, init\t Initialises the script to save username and password."
        echo "-l, login\t To directily login to  wifi."
        echo "-e, logout\t To logout of  wifi."
        ;;
    *)
        echo "Enter valid commands.."
esac
