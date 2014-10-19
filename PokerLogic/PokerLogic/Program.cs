using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using System.Drawing;
using System.Text.RegularExpressions;
using System.IO;
using System.Diagnostics;
using Microsoft.VisualBasic;


namespace PokerTableHelper
{


    class Program
    {

        private string pathToHH;
        private string yourName;
        private string[] fileLines = null;
        private int tableCounter = 0;
        static void Main()
        {
            Program x = new Program();


            if (MessageBox.Show("Do you want to create new user?", "New User?", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                StreamWriter writer = null;

                if (!System.IO.File.Exists("savedData.txt"))
                {

                    writer = System.IO.File.CreateText("savedData.txt");

                }
                else
                {
                    System.IO.File.Delete("savedData.txt");
                    writer = System.IO.File.CreateText("savedData.txt");

                }

                x.yourName = Interaction.InputBox("What is your name in the game?", "Please provide your name", "");
                x.pathToHH = Interaction.InputBox("Where does pokerstars store your HH?", "Please provide your HH path", "");
                writer.WriteLine(x.yourName);
                writer.WriteLine(x.pathToHH);
                writer.Flush();
            }
            else
            {
                x.fileLines = new String[2];
                x.fileLines = System.IO.File.ReadAllLines("savedData.txt");
                x.yourName = x.fileLines[0];
                x.pathToHH = x.fileLines[1];
            }
            x.TableThreadManipulation();



            Console.WriteLine("Waiting for Table..");



            Console.ReadLine();

        }


        private void TableThreadManipulation()
        {

            FileSystemWatcher watcher = new FileSystemWatcher();


            //watcher.Path = Path.GetDirectoryName(@"C:\Users\spiritinlife\Spiritinlife\"+ this.yourName +@"\");
            watcher.Path = Path.GetDirectoryName(this.pathToHH + this.yourName + @"\");

            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
             | NotifyFilters.FileName | NotifyFilters.DirectoryName;

            watcher.Filter = "*.txt";
            watcher.Created += new FileSystemEventHandler(onFileCreated);
            watcher.EnableRaisingEvents = true;

        }

        private void onFileCreated(object sender, FileSystemEventArgs e)
        {

            if (!e.Name.Contains("tmp"))  //do not take the temp files
            {

                Console.WriteLine("New table opened. Good Luck.");
                Thread thread = new Thread(new ThreadStart(delegate
                    {
                        Table table = new Table(yourName,tableCounter++);
                        table.startManipulation(e);
                    })
                );
                thread.Start();
            }
        }


        /*   public static IntPtr FindChildWindow(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszTitle)
           {
               // Try to find a match.
               IntPtr hwnd = FindWindowEx(hwndParent, IntPtr.Zero, lpszClass, lpszTitle);
               if (hwnd == IntPtr.Zero)
               {
                   // Search inside the children.
                   IntPtr hwndChild = FindWindowEx(hwndParent, IntPtr.Zero, null, null);
                   while (hwndChild != IntPtr.Zero && hwnd == IntPtr.Zero)
                   {
                       hwnd = FindChildWindow(hwndChild, IntPtr.Zero, lpszClass, lpszTitle);
                       if (hwnd == IntPtr.Zero)
                       {
                           // If we didn't find it yet, check the next child.
                           hwndChild = FindWindowEx(hwndParent, hwndChild, null, null);
                       }
                   }
               }
               return hwnd;
           }
           */
    }
}
