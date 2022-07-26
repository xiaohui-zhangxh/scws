# frozen_string_literal: true
require 'tempfile'

RSpec.describe Scws4r do
  it "has a version number" do
    expect(Scws4r::VERSION).not_to be nil
  end

  context '自定义分词' do
    it '请问探码科技怎么走' do
      subject.load_defaults
      rule_file = Tempfile.new 'scws-rule'
      rule_file.write <<~RULE
        探码科技  2.0 12.0
      RULE
      rule_file.close
      subject.add_dic rule_file.path, Scws4r::XDICT_TXT
      words = subject.split('请问探码科技怎么走才都到正在的探码科技')
      expect(words).to include(include("text" => '探码科技'))
    end
  end
end
