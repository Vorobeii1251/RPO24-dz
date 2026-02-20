using System;
using System.Linq;

namespace c_
{
    internal class para9
    {
        private Dictionary<string, int> shopItems;
        private int gold;
        private List<string> inventory;

        public para9()
        {
            shopItems = new Dictionary<string, int>()
            {
                {"Health Potion", 50},
                {"Mana Potion", 75},
                {"Sword", 200},
                {"Shield", 150},
                {"Bow", 180},
                {"Arrow", 10}
            };

            gold = 500;
            inventory = new List<string>();
        }

        public void Run()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            while (true)
            {
                ShowMainMenu();

                string choice = Console.ReadLine();

                switch (choice)
                {
                    case "1":
                        ShowShopItems();
                        break;
                    case "2":
                        ShowInventory();
                        break;
                    case "3":
                        BuyItem();
                        break;
                    case "4":
                        SellItem();
                        break;
                    case "5":
                        ManageShop(); 
                        break;
                    case "6":
                        Console.WriteLine("\nСпасибо за игру");
                        return;
                    default:
                        Console.WriteLine("\nНеверный выбор");
                        break;
                }

                Console.WriteLine("\nНажмите любую клавишу");
                Console.ReadKey();
                Console.Clear();
            }
        }

        private void ShowMainMenu()
        {
            Console.WriteLine("Игровой магазин");
            Console.WriteLine($"Ваше золото: {gold,4}");
            Console.WriteLine("");
            Console.WriteLine("1.Посмотреть товары");
            Console.WriteLine("2.Инвентарь");
            Console.WriteLine("3.Купить предмет");
            Console.WriteLine("4.Продать предмет");
            Console.WriteLine("5.Управление магазином (админ)");
            Console.WriteLine("6.Выход");
            Console.Write("Ваш выбор: ");
        }

        private void ShowShopItems()
        {
            Console.WriteLine("\nтовары в магазине:");

            if (shopItems.Count == 0)
            {
                Console.WriteLine("Магазин пуст");
                return;
            }

            int index = 1;
            foreach (var item in shopItems.OrderBy(x => x.Value))
            {
                string rarity = GetRarity(item.Value);
                Console.WriteLine($"{index,2}. {item.Key,-20} {item.Value,4} золота {rarity}");
                index++;
            }

            Console.WriteLine($"Всего товаров: {shopItems.Count}");
        }

        private string GetRarity(int price)
        {
            if (price < 50) return "Обычный";
            if (price < 100) return "Необычный";
            if (price < 200) return "Редкий";
            if (price < 300) return "Эпический";
            return "Легендарный";
        }

        private void ShowInventory()
        {
            Console.WriteLine("\nваш инвентарь:");

            if (inventory.Count == 0)
            {
                Console.WriteLine("Инвентарь пуст");
                return;
            }

            var groupedItems = inventory.GroupBy(x => x)
                                        .Select(g => new { Item = g.Key, Count = g.Count() })
                                        .OrderBy(x => x.Item);

            foreach (var item in groupedItems)
            {
                Console.WriteLine($"• {item.Item} x{item.Count}");
            }

            Console.WriteLine($"Золото: {gold}");
        }

        private void BuyItem()
        {
            Console.WriteLine("\nпокупка предмета:");

            if (shopItems.Count == 0)
            {
                Console.WriteLine("Магазин пуст");
                return;
            }

            ShowShopItems();
            Console.WriteLine("0. Отмена");

            Console.Write("\nВыберите номер товара для покупки: ");
            if (!int.TryParse(Console.ReadLine(), out int index) || index < 0 || index > shopItems.Count)
            {
                Console.WriteLine("Неверный номер");
                return;
            }

            if (index == 0)
            {
                Console.WriteLine("Операция отменена.");
                return;
            }

            var item = shopItems.ElementAt(index - 1);

            Console.Write($"Введите количество (макс. 10): ");
            if (!int.TryParse(Console.ReadLine(), out int quantity) || quantity < 1 || quantity > 10)
            {
                Console.WriteLine("Неверное количество");
                return;
            }

            int totalCost = item.Value * quantity;

            if (totalCost > gold)
            {
                Console.WriteLine($"мало золота, нужно {totalCost}, у вас {gold}");
                return;
            }

            // Подтверждение покупки
            Console.WriteLine($"Покупка: {item.Key} x{quantity} = {totalCost} золота");
            Console.Write("Подтвердить покупку? (да/нет): ");

            if (Console.ReadLine().ToLower() == "да")
            {
                gold -= totalCost;
                for (int i = 0; i < quantity; i++)
                {
                    inventory.Add(item.Key);
                }
                Console.WriteLine($"Покупка успешна, у вас осталось {gold} золота");
            }
            else
            {
                Console.WriteLine("Покупка отменена.");
            }
        }

        private void SellItem()
        {
            Console.WriteLine("\nпродажа предмета:");

            if (inventory.Count == 0)
            {
                Console.WriteLine("Инвентарь пуст");
                return;
            }

            ShowInventory();

            var uniqueItems = inventory.Distinct().ToList();

            Console.WriteLine("\n0. Отмена");
            Console.Write("Выберите предмет для продажи: ");

            if (!int.TryParse(Console.ReadLine(), out int choice) || choice < 0 || choice > uniqueItems.Count)
            {
                Console.WriteLine("Неверный выбор");
                return;
            }

            if (choice == 0)
            {
                Console.WriteLine("Операция отменена.");
                return;
            }

            string itemToSell = uniqueItems[choice - 1];
            int sellPrice = shopItems.ContainsKey(itemToSell) ? shopItems[itemToSell] / 2 : 10;

            Console.Write($"Введите количество для продажи: ");
            if (!int.TryParse(Console.ReadLine(), out int quantity) || quantity < 1)
            {
                Console.WriteLine("Неверное количество");
                return;
            }

            int itemCount = inventory.Count(x => x == itemToSell);
            if (quantity > itemCount)
            {
                Console.WriteLine($"У вас только {itemCount} предметов");
                return;
            }

            int totalEarn = sellPrice * quantity;

            Console.WriteLine($"Продажа: {itemToSell} x{quantity} = {totalEarn} золота");
            Console.Write("Подтвердить продажу? (да/нет): ");

            if (Console.ReadLine().ToLower() == "да")
            {
                gold += totalEarn;
                for (int i = 0; i < quantity; i++)
                {
                    inventory.Remove(itemToSell);
                }
                Console.WriteLine($"Продажа успешна, у вас {gold} золота");
            }
            else
            {
                Console.WriteLine("Продажа отменена.");
            }
        }

        private void ManageShop()
        {
            Console.WriteLine("\n управление магазином (админ):");
            Console.WriteLine("1. Добавить товар");
            Console.WriteLine("2. Удалить товар");
            Console.WriteLine("3. Изменить товар");
            Console.WriteLine("4. Статистика магазина");
            Console.WriteLine("5. Изменить золото игрока");
            Console.WriteLine("0. Назад");

            Console.Write("Выберите действие: ");
            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    AddItem();
                    break;
                case "2":
                    RemoveItem();
                    break;
                case "3":
                    UpdateItem();
                    break;
                case "4":
                    ShowShopStats();
                    break;
                case "5":
                    ModifyPlayerGold();
                    break;
                case "0":
                    return;
                default:
                    Console.WriteLine("Неверный выбор");
                    break;
            }
        }

        private void AddItem()
        {
            Console.WriteLine("\nдобавление товара:");

            Console.Write("Название: ");
            string name = Console.ReadLine().Trim();

            if (string.IsNullOrEmpty(name))
            {
                Console.WriteLine("Название не может быть пустым");
                return;
            }

            if (shopItems.ContainsKey(name))
            {
                Console.WriteLine($"Товар '{name}' уже существует");
                return;
            }

            Console.Write("Цена: ");
            if (!int.TryParse(Console.ReadLine(), out int price) || price <= 0)
            {
                Console.WriteLine("Неверная цена");
                return;
            }

            shopItems.Add(name, price);
            Console.WriteLine($"Товар '{name}' добавлен");
        }

        private void RemoveItem()
        {
            Console.WriteLine("\nудаление товара:");

            if (shopItems.Count == 0)
            {
                Console.WriteLine("Магазин пуст");
                return;
            }

            ShowShopItems();
            Console.Write("Введите номер товара для удаления: ");

            if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > shopItems.Count)
            {
                Console.WriteLine("Неверный номер");
                return;
            }

            var item = shopItems.ElementAt(index - 1);
            shopItems.Remove(item.Key);
            Console.WriteLine($"Товар '{item.Key}' удален");
        }

        private void UpdateItem()
        {
            Console.WriteLine("\nизменение товара:");

            if (shopItems.Count == 0)
            {
                Console.WriteLine("Магазин пуст");
                return;
            }

            ShowShopItems();
            Console.Write("Выберите номер товара для изменения: ");

            if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > shopItems.Count)
            {
                Console.WriteLine("Неверный номер");
                return;
            }

            var item = shopItems.ElementAt(index - 1);

            Console.WriteLine($"Текущий товар: {item.Key} - {item.Value}");
            Console.Write("Новое название (Enter - оставить): ");
            string newName = Console.ReadLine().Trim();

            Console.Write("Новая цена (Enter - оставить): ");
            string priceInput = Console.ReadLine();

            if (!string.IsNullOrEmpty(newName) && newName != item.Key)
            {
                if (shopItems.ContainsKey(newName))
                {
                    Console.WriteLine("Такое название уже существует");
                }
                else
                {
                    shopItems.Remove(item.Key);
                    shopItems.Add(newName, item.Value);
                    item = new KeyValuePair<string, int>(newName, item.Value);
                }
            }

            if (!string.IsNullOrEmpty(priceInput) && int.TryParse(priceInput, out int newPrice) && newPrice > 0)
            {
                shopItems[item.Key] = newPrice;
            }

            Console.WriteLine("Товар обновлен");
        }

        private void ShowShopStats()
        {
            Console.WriteLine("\nстатистика магазина:");

            int totalValue = shopItems.Values.Sum();
            double averagePrice = shopItems.Values.Average();
            int cheapest = shopItems.Values.Min();
            int mostExpensive = shopItems.Values.Max();

            var cheapestItem = shopItems.First(x => x.Value == cheapest);
            var expensiveItem = shopItems.First(x => x.Value == mostExpensive);

            Console.WriteLine($"Всего товаров: {shopItems.Count}");
            Console.WriteLine($"Общая стоимость: {totalValue} золота");
            Console.WriteLine($"Средняя цена: {averagePrice:F1} золота");
            Console.WriteLine($"Самый дешевый: {cheapestItem.Key} ({cheapest} золота)");
            Console.WriteLine($"Самый дорогой: {expensiveItem.Key} ({mostExpensive} золота)");
        }

        private void ModifyPlayerGold()
        {
            Console.WriteLine($"\nТекущее золото игрока: {gold}");
            Console.Write("Введите новое количество золота: ");

            if (int.TryParse(Console.ReadLine(), out int newGold) && newGold >= 0)
            {
                gold = newGold;
                Console.WriteLine($"Золото изменено на {gold}");
            }
            else
            {
                Console.WriteLine("Неверное значение");
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            para9 shop = new para9();
            shop.Run();
        }
    }

}
