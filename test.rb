require 'scws'
s = Scws.new
s.charset='utf8'
s.add_dic '/Users/xiaohui/coding/postgresql-zhparser/zhparser/dict.utf8.xdb'
a=s.split(ARGV[0] || 'Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言')
puts a
