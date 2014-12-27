#include "fixtures.h"
#include "ui_fixtures.h"

Fixtures::Fixtures(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Fixtures)
{
    ui->setupUi(this);

    ui->dockWidgetContents->setLayout(ui->verticalLayout);

    readStructureInfo();
}

Fixtures::~Fixtures()
{
    delete ui;
}

void Fixtures::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}

void Fixtures::unselectAll()
{
    ui->listView->clearSelection();
}

void Fixtures::readStructureInfo()
{
    /*FixtureStructure DATA;
    FixtureInfo infoFixt;
    string Line;
    ifstream file;
    int pos, bufferCalculs ,octetsParFixture, octetsTotal;
    bufferCalculs=0;
    octetsTotal = 0;
    nombreDAdresses = 0;
    int adresseTmp = 0 , buffer = 0;

    file.open(path.toUtf8());

    if(file.is_open()==false){
        QMessageBox::warning(this, "Error", "Verify that there is a descriptive file at _____\n");
        return;
    }

    //Initialisation
    for(int a=0; a<8; a++)
    {
        infoFixt.sliderActive[a]=false;
        infoFixt.bitsParSlider[a] = 0;
    }
    DATA.nombre_de_fixture = 0;


    while(getline(file, Line))
    {

        if(!Line.compare(0,1,"#"))
        {
            //on fait rien c'est un commentaire
        }
        else if(!Line.compare(0,8,"_Fixture"))
        {
            //on regarde le dernier lu pour setter l'adresse du prochain
            buffer = 0;
            for(int a=0; a<8; a++)
            {
                buffer += infoFixt.bitsParSlider[a];
            }
            adresseTmp += buffer/8;

            if(buffer%8 != 0)
                adresseTmp++;

            //On set l'adresse de la fixture tout suite
            infoFixt.adresse = adresseTmp;


            //--- On delete les infos du dernier (pour une couple de ligne encore)---
            for(int a=0; a<8; a++)
            {
                infoFixt.sliderActive[a]=false;
                infoFixt.bitsParSlider[a] = 0;
            }

            // numero de la fixture
            pos = Line.find(' ');
            Line.erase(0,pos+1);
            /*istringstream numeroFixture(Line);
            numeroFixture >> DATA.nombre_de_fixture;*/
            /*DATA.nombre_de_fixture++;
            infoFixt.identifiant = DATA.nombre_de_fixture;


            // Nom de la fixture
            getline(file, Line);
            QString nomDeLaFixture(Line.c_str());
            infoFixt.FixtureName = nomDeLaFixture;

            //on initialise les noms � rien
            infoFixt.faderName[0]="";
            infoFixt.faderName[1]="";
            infoFixt.faderName[2]="";
            infoFixt.faderName[3]="";
            infoFixt.faderName[4]="";
            infoFixt.faderName[5]="";
            infoFixt.faderName[6]="";
            infoFixt.faderName[7]="";



            for(int i = 0; i<8; i++)
            {
                getline(file,Line);

                if(Line.empty())
                {
                    //ca veut dire qu'on a
                    //fini pour cette fixture
                    //et on sort de la boucle
                    break;
                }
                else
                {

                    istringstream numeroDuFader(Line);
                    int numeroFader;
                    numeroDuFader >> numeroFader;

                    infoFixt.sliderActive[numeroFader-1]=true;
                    Line.erase(0,2);

                    if(!Line.compare(0,1,"_"))
                    {
                        //on ramasse le code
                        if(!Line.compare(0,4,"_POS"))
                        {
                            infoFixt.bitsParSlider[numeroFader-1] = 8;
                            infoFixt.mode[numeroFader-1] = POS;
                            Line.erase(0,5);    //on efface
                        }
                    }

                    else
                    {
                        istringstream bitsParFader(Line);
                        bitsParFader >> infoFixt.bitsParSlider[numeroFader-1];
                        infoFixt.mode[numeroFader-1] = NOMODE;

                        Line.erase(0,2);
                    }

                    QString nomDuFader(Line.c_str());
                    infoFixt.faderName[numeroFader-1] = nomDuFader;


                }
            }
            DATA.infoFixture<<infoFixt;



            //////////////////////////////////////////////////
            //On set pour l'envoit �lectronique             //
            octetsParFixture = 0;                           //
            bufferCalculs = 0;                              //
                                                            //
            for(int i = 0; i<8; i++)                        //
            {                                               //
                bufferCalculs += infoFixt.bitsParSlider[i]; //
            }                                               //
                                                            //
            octetsParFixture = bufferCalculs/8;             //
            //si arrive pas juste, on doit ajouter 1        //
            if(bufferCalculs%8!=0){                         //
                octetsParFixture++;                         //
                }                                           //
            //////////////////////////////////////////////////

            octetsTotal+=octetsParFixture;

        }
    }

    faderValue = new int[octetsTotal];
    nombreDAdresses = octetsTotal;
    for(int i =0; i < nombreDAdresses; i++)
    {
        faderValue[i] = 0;
    }

    ui->labelTotalAdressValue->setNum(nombreDAdresses); //on �crit combiens il y a d'addresses

    emit setStructure(DATA);                            //on �met pour dire que c'est charg�
    CopieFixtureStructure = DATA;                       //on fait une copie

    //on pr�set tout � sa valeur par d�faut
    for(int i = 0; i<CopieFixtureStructure.nombre_de_fixture; i++)
    {
        SliderPos sliderTmp;

        for(int a = 0; a < 8; a++)
        {
            if(CopieFixtureStructure.infoFixture.at(i).mode[a] == POS){
                sliderTmp.slider[a] = 165;
            }
            else{
                sliderTmp.slider[a] = 0;
            }
        }

        setSliderBuffer(i+1, sliderTmp);
    }

    file.close();
    return;*/
}
