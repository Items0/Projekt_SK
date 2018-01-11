using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.IO;
namespace Klient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }

        public class pair
        {
            public string name;
            public string IP;
        }

        public static class MyList
        {
            public static List<pair> myList = new List<pair>();
        }
        

        private void doIT()
        {
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                if (checkedListBox1.GetItemChecked(i))
                {
                    System.Net.Sockets.TcpClient clientSocket = new System.Net.Sockets.TcpClient(); // --SOCKET() - utworzenie gniazda
                    try
                    {
                        //MessageBox.Show(MyList.myList[i].IP);
                        clientSocket.Connect(MyList.myList[i].IP, 1235); // --CONNECT()
                        //MessageBox.Show("Udalo sie");
                        NetworkStream serverStream = clientSocket.GetStream();
                        byte[] outStream = System.Text.Encoding.ASCII.GetBytes("shutdownX");
                        serverStream.Write(outStream, 0, outStream.Length);
                        serverStream.Flush();

                        //BinaryWriter writer = new BinaryWriter(clientSocket.GetStream());
                        //writer.Write("Hey");
                        //BinaryReader reader = new BinaryReader(clientSocket.GetStream());
                        //Console.WriteLine(reader.ReadString());
                        /*byte[] inStream = new byte[10025];
                        serverStream.Read(inStream, 0, (int)clientSocket.ReceiveBufferSize);
                        string returndata = System.Text.Encoding.ASCII.GetString(inStream);
                        MessageBox.Show(returndata);*/
                        NetworkStream networkStream = clientSocket.GetStream();
                        // Set a 10 millisecond timeout for reading.
                        networkStream.ReadTimeout = 10000;
                        // Read the server message into a byte buffer.
                        byte[] bytes = new byte[1024];
                        networkStream.Read(bytes, 0, 1024);
                        //Convert the server's message into a string and display it.
                        string data = Encoding.UTF8.GetString(bytes);
                        Console.WriteLine("Server sent message: {0}", data);

                        clientSocket.Close();
                        //MessageBox.Show(reader.ReadString());
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show("Nie udalo sie polaczyc");
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            doIT();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            pair myPair = new pair();
            myPair.name = textBox2.Text;
            myPair.IP = textBox3.Text;
            MyList.myList.Add(myPair);
            checkedListBox1.Items.Insert(checkedListBox1.Items.Count,myPair.name + "\t" + myPair.IP);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < checkedListBox1.Items.Count; i++)

                checkedListBox1.SetItemChecked(i, true);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < checkedListBox1.Items.Count; i++)

                checkedListBox1.SetItemChecked(i, false);
        }

    }
}
