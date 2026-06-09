using System;

class Order
{
    private static int nextId = 1;
    public int OrderId { get; private set; }

    public Order()
    {
        OrderId = nextId;
        nextId++;
    }

    public void DisplayInfo()
    {
        Console.WriteLine($"Order #{OrderId}");
    }
}

class Program
{
    static void Main()
    {
        Order order1 = new Order();
        Order order2 = new Order();
        Order order3 = new Order();
        Order order4 = new Order();

        order1.DisplayInfo();
        order2.DisplayInfo();
        order3.DisplayInfo();
        order4.DisplayInfo();
    }
}