using System;
using System.Threading;

/*---------Main module----------
Parallel and Distributed Computing
Coursework. PRG1 
Kovbasa Sviatoslav
IO-53
23.03.2018
A = sort(d * B + C * (MO * MX))
*/
namespace PRG1
{
    class PRG1
    {
        //Size of arrays
        static int n;

        //Number of threads
        static int p;

        //Size of the parts of arrays in threads
        static int h;

        //Number of levels in merging
        static int m;

        //Input data
        static int[] A, B, C, D, E;
        static int[][] MO, MX, MZ;
        static int d;
        static ManualResetEvent[] events;
        static ManualResetEvent[] events1;
        static Semaphore sem;
        static Mutex mut;
        static Semaphore[] sems;
        static object thisLock = new object();
        static string result = "";

        private static void Tifunc()
        {
            Thread currThread = Thread.CurrentThread;
            System.Console.WriteLine("T" + currThread.Name + " started");
            int tid = int.Parse(currThread.Name);

            //1. If tid == 0, read B, C and MX.
            if (tid == 0)
            {
                Vector.Fill(B, 1);
                Vector.Fill(C, 1);
                Matrix.Fill(MX, 1);
                //2. If tid == 0, send the signal to all the other threads.
                events[0].Set();
            }

            //3. If tid == p-1, read MO and d.
            if (tid == p - 1)
            {
                d = 1;
                Matrix.Fill(MO, 1);
                //4. If tid == p-1, send the signal to all the other threads.
                events[1].Set();
            }

            //5. Wait for signals from T0 and Tp-1
            WaitHandle.WaitAll(events);

            int[][] MXi;
            int[] Ci;
            int di;

            //6. Copying MX
            lock (thisLock)
            {
                MXi = Matrix.GetCopy(MX);
            }

            //7. Copying C
            mut.WaitOne();
            Ci = Vector.GetCopy(C);
            mut.ReleaseMutex();


            //8. Copying d
            sem.WaitOne();
            di = d;
            sem.Release();

            int i1 = tid * h;
            int i2 = (tid + 1) * h;

            //9. Calculations 1
            Matrix.Multiply(MO, MXi, MZ, i1, i2);
            Vector.Multiply(Ci, MZ, D, i1, i2);
            Vector.Multiply(B, di, E, i1, i2);
            Vector.Add(E, D, A, i1, i2);
            Vector.Sort(A, i1, i2);

            //10. Signal of the end of calculations 1
            sems[tid].Release(p);
            //11. Waiting for the end of calculations 1
            WaitHandle.WaitAll(sems);

            int first1, last1, last2;
            //12. Calculations 2
            for (int i = 0; i < m; i++)
            {
                events1[tid].Reset();
                if (tid % Math.Floor(Math.Pow(2, i + 1)) == 0)
                {
                    first1 = i1;
                    last1 = first1 + (int)Math.Floor(Math.Pow(2, i)) * h - 1;
                    last2 = last1 + (int)Math.Floor(Math.Pow(2, i)) * h;
                    if (last2 >= n) last2 = n - 1;
                    Vector.Merge(A, first1, last1, last2);
                }
                //13. Signal of the end of calculations 2.m
                events1[tid].Set();
                //14. Wait for the end of calculations 2.m
                WaitHandle.WaitAll(events1);
            }

            //15. Output A
            if (tid == p - 1)
                if (n <= 12)
                    Console.WriteLine(Vector.ToString(A));

            Console.WriteLine("T" + currThread.Name + " finished");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Turn off unused cores and press enter to continue");
            Console.Read();
            p = Int32.Parse(args[0]);
            m = (int)Math.Ceiling(Math.Log(p, 2));
            Thread[] threads = new Thread[p];
            int[] testLengths = { 900, 1800, 2400 };
            for (int index = 0; index < testLengths.Length; index++)
            {
                n = testLengths[index];
                h = n / p;
                var watch = System.Diagnostics.Stopwatch.StartNew();
                events = new ManualResetEvent[2];
                events[0] = new ManualResetEvent(false);
                events[1] = new ManualResetEvent(false);

                mut = new Mutex();
                sem = new Semaphore(1, 1);

                A = new int[n];
                B = new int[n];
                C = new int[n];
                D = new int[n];
                E = new int[n];

                MO = new int[n][];
                MX = new int[n][];
                MZ = new int[n][];
                for (int i = 0; i < n; i++)
                {
                    MO[i] = new int[n];
                    MX[i] = new int[n];
                    MZ[i] = new int[n];
                }

                sems = new Semaphore[p];
                for (int i = 0; i < p; i++)
                    sems[i] = new Semaphore(0, p);

                events1 = new ManualResetEvent[p];
                for (int i = 0; i < p; i++)
                    events1[i] = new ManualResetEvent(false);

                //Creating threads
                threads = new Thread[p];
                for (int i = 0; i < p; i++)
                {
                    threads[i] = new Thread(Tifunc, 1000)
                    {
                        Priority = ThreadPriority.Highest,
                        Name = i.ToString()
                    };
                    threads[i].Start();
                }
                for (int i = 0; i < p; i++)
                {
                    threads[i].Join();
                }

                watch.Stop();
                var elapsedMs = watch.ElapsedMilliseconds;
                result += "N: " + n + Environment.NewLine +
                    "P: " + p + Environment.NewLine +
                    "Time: " + elapsedMs + " ms" + Environment.NewLine + Environment.NewLine;
            }
            System.IO.File.WriteAllText(@"./result" + p + ".txt", result);
        }
    }
}
