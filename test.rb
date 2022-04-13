require 'scws4r'
s = Scws4r.new
s.charset='utf8'
s.add_dic '/Users/xiaohui/coding/postgresql-zhparser/zhparser/dict.utf8.xdb', Scws4r::XDICT_XDB
a=s.split(ARGV[0] || 'Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言')
puts a
puts '------------'
s.multi = Scws4r::MULTI_SHORT | Scws4r::MULTI_DUALITY
s.multi = Scws4r::MULTI_DUALITY
s.punctuation_ignore = true
# s.duality = true
a=s.split(ARGV[0] || 'Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言')
puts a
puts '------------'
a=s.tops(ARGV[0] || 'Hello, 我名字叫李那曲是一个中国人, 我有时买Q币来玩, 我还听说过C#语言', 10)
puts a
