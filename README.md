# SCWS(Simple Chinese Word Segmentation) for Ruby

This is a Ruby gem integrated with [scws](https://github.com/hightman/scws/blob/master/API.md) C lib

## Installation

Install the gem and add to the application's Gemfile by executing:

    $ bundle add scws4r

If bundler is not being used to manage dependencies, install the gem by executing:

    $ gem install scws4r

## Usage

```ruby
2.7.2 :001 > require 'scws4r'
 => true
2.7.2 :002 > s = Scws4r.new
 => #<Scws4r:0x00007fbc2b1bc878>
2.7.2 :003 > s.load_defaults
 => false
2.7.2 :004 > puts s.split('保障房资金压力')
{"offset"=>0, "idf"=>4.889999866485596, "length"=>6, "text"=>"保障", "attr"=>"vn"}
{"offset"=>6, "idf"=>0.0, "length"=>3, "text"=>"房", "attr"=>"n"}
{"offset"=>9, "idf"=>4.880000114440918, "length"=>6, "text"=>"资金", "attr"=>"n"}
{"offset"=>15, "idf"=>4.900000095367432, "length"=>6, "text"=>"压力", "attr"=>"n"}
 => nil
2.7.2 :005 > puts s.tops('保障房资金压力', 10)
{"times"=>1, "weight"=>4.900000095367432, "word"=>"压力", "attr"=>"n"}
{"times"=>1, "weight"=>4.889999866485596, "word"=>"保障", "attr"=>"vn"}
{"times"=>1, "weight"=>4.880000114440918, "word"=>"资金", "attr"=>"n"}
 => nil
2.7.2 :006 >
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and the created tag, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## references

- https://docs.ruby-lang.org/en/2.4.0/extension_rdoc.html

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/scws.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
