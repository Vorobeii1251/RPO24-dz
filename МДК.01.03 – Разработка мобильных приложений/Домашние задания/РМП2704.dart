
final now = DateTime.now();
final months = [
  'января', 'февраля', 'марта', 'апреля', 'мая', 'июня',
  'июля', 'августа', 'сентября', 'октября', 'ноября', 'декабря'
];
final dateStr = '${now.day} ${months[now.month - 1]} ${now.year}';

tp = TextPainter(
  text: TextSpan(
    text: 'Дата: $dateStr',
    style: const TextStyle(fontSize: 14, color: Color(0xFF9E9E9E)),
  ),
  textAlign: TextAlign.center,
  textDirection: TextDirection.ltr,
);
tp.layout(maxWidth: width - 80);
tp.paint(canvas, Offset((width - tp.width) / 2, height - 40)); 