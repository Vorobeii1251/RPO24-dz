using System;

class DatabaseConnector
{
    private static string connectionString;

    static DatabaseConnector()
    {
        connectionString = "Server=localhost;DB=Test";
        Console.WriteLine("Static constructor called");
    }

    public DatabaseConnector()
    {
        Console.WriteLine("Instance created");
    }

    public void Connect()
    {
        Console.WriteLine($"Connecting with: {connectionString}");
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("Creating first instance:");
        DatabaseConnector db1 = new DatabaseConnector();
        db1.Connect();

        Console.WriteLine("\nCreating second instance:");
        DatabaseConnector db2 = new DatabaseConnector();
        db2.Connect();

        Console.WriteLine("\nCreating third instance:");
        DatabaseConnector db3 = new DatabaseConnector();
        db3.Connect();
    }
}