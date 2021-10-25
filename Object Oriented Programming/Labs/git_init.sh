#!/bin/bash

main() {
    operation=notDone;
    while [ $operation != Done ]; do
        printMenu;
        readChoice123456;
        
        case $userAnswer123456 in
            1 )
                gitInit ;;
            2 )
                pullRepo ;;
            3 )
                pushRepo ;;
            4 )
                uninitializeRepo ;;
            5)
                deleteRepo ;;
            6 )
                operation=Done ;;
        esac
        
    done
}

############################### PRINT MENU #####################################
printMenu() {
    echo ""
    echo "********** MENU **********"
    echo "1. Initialize a repository and push it"
    echo "2. Pull a repository"
    echo "3. Push an updated repository"
    echo "4. Uninitialize an initialized repository"
    echo "5. Delete a directory"
    echo "6. Exit"
    echo ""
    printf "Choose [1-6]: "
}

readChoice123456() {
    userAnswer123456=q
    read userAnswer123456
    validation123456;
}

validation123456() {
    valid=false
    if [[ $userAnswer123456 =~ ^[1-6]$ ]]
    then
        valid=true
    fi
    
    while [ $valid != true ]; do
        printf "The answer is invalid. Please type in valid choice [1-6]: "
        read userAnswer123456
        if [[ $userAnswer123456 =~ ^[1-6]$ ]]
        then
            valid=true
        fi
    done
}

############################ INITIALIZE REPO AND PUSH #####################################
gitInit() {
    echo ""
    echo "List of folders:"
    echo ""
    ls -d */
    echo ""
    echo "Which folder would you like to initialize with git?"
    echo ""
    printf "Choice ['back' is to return to the main menu]: "
    read DIRECTORY
    if [ "$DIRECTORY" == "back" ]
    then
        return 0
    fi
    
    if test -d $DIRECTORY
    then
        if test -d .git
        then
            echo ""
            echo "The folder is already initialized with git."
            return 0
        fi
        
		userAnswerYN=q
        while [ "$userAnswerYN" != "y" ]; do
            echo ""
            printf "Your first name: "
            read firstName

            echo ""
            printf "Your last name: "
            read lastName

            echo ""
            printf "Your email: "
            read email
            
            echo ""
            printf "Your comment to the repository: "
            read comment

            echo ""
            echo "Confirm the infromation:"
            echo "Full name: $firstName $lastName"
            echo "Email:     $email"
            echo "Comment:   $comment"
            echo ""
            printf "Answer [y/n]: "
            read userAnswerYN
            validationYN;
        done
        
        echo ">> cd $DIRECTORY"
        cd $DIRECTORY
        
        echo ">> git init"
        git init
        
        echo ">> git config --global user.name $firstName $lastName"
        git config --global user.name $firstName $lastName
        
        echo ">> git config --local user.name $firstName $lastName"
        git config --local user.name $firstName $lastName
        
        echo ">> git config --global user.email $email"
        git config --global user.email $email
        
        echo ">> git config --local user.email $email"
        git config --local user.email $email
        
        echo ""
        echo ">> git status"
        git status
        
        echo ""
        echo ">> git add *"
        git add *
        
        echo ""
        echo ">> git status"
        git status
        
        echo ""
        echo ">> git commit -m $comment"
        git commit -m "$comment"
        
        echo ""
        echo ">> git status"
        git status
        
        echo ""
        echo "The folder called $DIRECTORY is initialized with git."
        
        
        userAnswerYN=q
        while [ "$userAnswerYN" != "y" ]; do
            echo ""
            printf "Bitbucket account you would like to push to: "
            read BitbucketAccount

            echo ""
            printf "Folder on the account to which you would like to push the internals of the folder $DIRECTORY: "
            read folder
            
            echo ""
            echo "Would like to push to the address below?"
            echo ""
            printf "https://bitbucket.org/$BitbucketAccount/$folder.git"
            echo ""
            printf "Answer [y/n]: "
            read userAnswerYN
            validationYN
        done
        
        echo ""
        echo ">> git remote add origin https://bitbucket.org/$BitbucketAccount/$folder.git"
        git remote add origin https://bitbucket.org/$BitbucketAccount/$folder.git
        
        echo ""
        echo ">> git push -u origin master"
        git push -u origin master
        
        echo ""
        echo ">> cd .."
        cd ..
        
        return 0
    fi
    
    echo ""
    echo "Directory called $DIRECTORY does not exist."
    return 0
}

############################### PULL REPO ######################################
pullRepo() {
    userAnswerYN=q
    while [ "$userAnswerYN" != "y" ]; do
        echo ""
        echo "From which Bitbucket account would you like to pull?"
        echo ""
        printf "Choice ['back' is to return to the main menu]: "
        read BitbucketAccount

        if [ "$BitbucketAccount" == "back" ]
        then
            return 0
        fi

        printf "Folder on the account that you would like to pull: "
        read folder

        echo ""
        echo "Would like to pull from the address below?"
        echo ""
        printf "https://bitbucket.org/$BitbucketAccount/$folder.git"
        echo ""
        printf "Answer [y/n]: "
        read userAnswerYN
        validationYN
    done
    
    if test -d $folder
    then
        echo ""
        echo ">> cd $folder"
        cd $folder
        
        echo ""
        echo ">> git pull"
        git pull
        
        echo ""
        echo ">> cd .."
        cd ..
        
        return 0
    fi
    
    echo ">> git clone  https://bitbucket.org/$BitbucketAccount/$folder.git"
    git clone  https://bitbucket.org/$BitbucketAccount/$folder.git
}

validationYN() {
    while [ "$userAnswerYN" != "y" ] && [ "$userAnswerYN" != "n" ]; do
        printf "The answer is invalid. Please type in valid choice [y/n]: "
        read userAnswerYN
    done
}

################################ PUSH REPO ###################################
pushRepo() {
    echo ""
    echo "List of folders:"
    echo ""
    ls -d */
    echo ""
    echo "Which folder would you like to push?"
    echo ""
    printf "Choice ['back' is to return to the main menu]: "
    read DIRECTORY
    if [ "$DIRECTORY" == "back" ]
    then
        return 0
    fi
    
    if test -d $DIRECTORY
    then
        echo ""
        echo ">> cd $DIRECTORY"
        cd $DIRECTORY
        
        if test -d .git
        then
            echo ""
            printf "Comment you would like to add to the repository: "
            read comment
            
            echo ""
            echo ">> git pull"
            git pull
        
            echo ""
            echo ">> git status"
            git status

            echo ""
            echo ">> git add *"
            git add *

            echo ""
            echo ">> git status"
            git status

            echo ""
            echo ">> git commit -m $comment"
            git commit -m "$comment"

            echo ""
            echo ">> git status"
            git status

            echo ""
            echo ">> git push"
            git push
            
			
			
            echo "The folder has been updated on the Bitbucket account."
            
            return 0
        fi
		
	   echo ""
	   echo ">> cd .."
	   cd ..
        
        echo ""
        echo "The folder is not initialized with git."
        
        return 0;
    fi
    
    echo ""
    echo "Directory called $DIRECTORY does not exist."
    return 0
}

########################### UN-INITIALIZE REPO ####################################
uninitializeRepo() {
    echo ""
    echo "List of folders:"
    echo ""
    ls -d */
    echo ""
    echo "Which folder would you like to delete?"
    echo ""
    printf "Choice ['back' is to return to the main menu]: "
    read DIRECTORY
    if [ "$DIRECTORY" == "back" ]
    then
        return 0
    fi
    
    if test -d $DIRECTORY
    then
        echo ""
        echo ">> cd $DIRECTORY"
        cd $DIRECTORY
        
        echo ""
        echo ">> rm -rf .git"
        rm -rf .git
        
        echo ""
        echo ">> cd .."
        cd ..
        
        return 0
    fi
    
    echo ""
    echo "Directory called $DIRECTORY does not exist."
}

################################## DELETE A REPO #####################################
deleteRepo() {
    echo ""
    echo "List of folders:"
    echo ""
    ls -d */
    echo ""
    echo "Which folder would you like to delete?"
    echo ""
    printf "Choice ['back' is to return to the main menu]: "
    read DIRECTORY
    if [ "$DIRECTORY" == "back" ]
    then
        return 0
    fi
    
    if test -d $DIRECTORY
    then
        echo ""
        echo ">> rm -rf $DIRECTORY"
        rm -rf $DIRECTORY
        
        echo ""
        echo "Directory called $DIRECTORY is deleted."
        
        return 0;
    fi
    
    echo ""
    echo "Directory called $DIRECTORY does not exist."
}

main