// Système de gestion d'un centre médical
using TP1;

try
{
   DoctorManager doctorMgr = new();
   PatientManager patientMgr = new(doctorMgr);

   Execute(patientMgr, doctorMgr);
}
catch (Exception exception)
{
   Console.WriteLine(exception.Message);
}





// Exécute la boucle principal du programme
void Execute(PatientManager patientMgr, DoctorManager doctorMgr)
{
   while (true)
   {
      string choice = AskMainChoice();

      switch (choice)
      {
         case "P":
            ExecutePrintOptions(patientMgr, doctorMgr);
            break;
         case "A":
            ExecuteAddOptions(patientMgr, doctorMgr);
            break;
         case "R":
            PrintTitle("Prise de rendez-vous");
            patientMgr.MakeAppointment();
            Pause();
            break;
         case "Q":
            doctorMgr.Save();
            patientMgr.Save();
            return;
         default:
            Console.WriteLine("Choix invalide");
            Pause();
            break;
      }
   }
}


// Affiche le menu principal, et retourne le choix de l'utilisateur
string AskMainChoice()
{
   PrintTitle("Centre médical");
   Console.WriteLine(" P) Affichage");
   Console.WriteLine(" A) Ajout");
   Console.WriteLine(" R) Prendre rendez-vous");
   Console.WriteLine(" Q) Quitter");
   Console.Write("\nChoix: ");

   return Console.ReadLine().Trim().ToUpper();
}


// Execute les options d'affichage
void ExecutePrintOptions(PatientManager patientMgr, DoctorManager doctorMgr)
{
   while (true)
   {
      string choice = AskPrintChoice();

      switch (choice)
      {
         case "P":
            PrintTitle("Liste des patients");
            patientMgr.Print();
            break;
         case "M":
            PrintTitle("Liste des médecins");
            doctorMgr.Print();
            break;
         case "R":
            return;
         default:
            Console.WriteLine("Choix invalide");
            break;
      }

      Pause();
   }
}


// Affiche le menu d'affichage, et retourne le choix de l'utilisateur
string AskPrintChoice()
{
   PrintTitle("Centre médical - Affichage");
   Console.WriteLine(" P) Afficher les patients");
   Console.WriteLine(" M) Afficher les médecins");
   Console.WriteLine(" R) Retour au menu principal");
   Console.Write("\nChoix: ");

   return Console.ReadLine().Trim().ToUpper();
}


// Execute les options d'ajout
void ExecuteAddOptions(PatientManager patientMgr, DoctorManager doctorMgr)
{
   while (true)
   {
      string choice = AskAddChoice();

      switch (choice)
      {
         case "P":
            PrintTitle("Ajout d'un patient");
            patientMgr.Add();
            break;
         case "M":
            PrintTitle("Ajout d'un médecin");
            doctorMgr.Add();
            break;
         case "R":
            return;
         default:
            Console.WriteLine("Choix invalide");
            break;
      }

      Pause();
   }
}


// Affiche le menu d'ajout, et retourne le choix de l'utilisateur
string AskAddChoice()
{
   PrintTitle("Centre médical - Ajout");
   Console.WriteLine(" P) Ajouter un patient");
   Console.WriteLine(" M) Ajouter un médecin");
   Console.WriteLine(" R) Retour au menu principal");
   Console.Write("\nChoix: ");

   return Console.ReadLine().Trim().ToUpper();
}


// Affiche le titre donné avec une décoration
void PrintTitle(string title)
{
   const int Longueur = 80;
   const string Start = "= ";
   const string End = "=";

   string line = new string('=', Longueur);
   title = title.PadRight(Longueur - Start.Length - End.Length);

   Console.Clear();
   Console.WriteLine("{0}\n{1}{2}{3}\n{0}\n", line, Start, title, End);
}


// Pause le programme pour permettre à l'utilisateur de lire la console
void Pause()
{
   Console.WriteLine("\n\nAppuyez sur une touche pour continuer...");
   Console.ReadKey(true);
}
