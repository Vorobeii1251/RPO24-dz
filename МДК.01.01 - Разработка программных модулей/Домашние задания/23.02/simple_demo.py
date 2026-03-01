from recipe_repository import RecipeRepository


def demo_basic_functions():

    print(" ДЕМО: 4 основные функции репозитория")
    print("=" * 40)

    repo = RecipeRepository()

    print("\n get_all() - все рецепты:")
    for r in repo.get_all():
        print(f"   [{r['id']}] {r['title']} ({r['category']})")

    print("\n get_by_category('Салаты'):")
    for r in repo.get_by_category('Салаты'):
        print(f"   - {r['title']}")

    print("\n add() - добавляем новый:")
    new_id = repo.add({
        'title': 'Блины',
        'category': 'Завтраки',
        'ingredients': ['Мука', 'Яйца', 'Молоко', 'Сахар'],
        'instructions': '1. Смешать ингредиенты\n2. Испечь блины'
    })
    print(f"    Добавлен с ID {new_id}")

    print("\n delete() - удаляем ID 1:")
    repo.delete(1)

    print("\n Итоговый список:")
    for r in repo.get_all():
        print(f"   [{r['id']}] {r['title']}")


if __name__ == "__main__":
    demo_basic_functions()