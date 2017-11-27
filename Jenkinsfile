pipeline {
    agent any
    triggers {
        pollSCM 'H/30 * * * *'
    }
    stages {
        stage('Prepare') {
            steps {
                sh 'echo "Skipping prepare.sh script call to speed up tests. Prerequisites should already be installed." # sh prepare.sh'
            }
        }
        stage('Build') {
            steps {
                sh 'sh build.sh'
            }
        }
    }
}
