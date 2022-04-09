# frozen_string_literal: true

require_relative "lib/scws4r/version"

Gem::Specification.new do |spec|
  spec.name = "scws4r"
  spec.version = Scws4r::VERSION
  spec.authors = ["xiaohui"]
  spec.email = ["xiaohui@tanmer.com"]

  spec.summary = "Integrate (SCWS) Simple Chinese Word Segmentation C lib"
  spec.description = "With SCWS to split Chinese sentences"
  spec.homepage = "https://github.com/xiaohui-zhangxh/scws"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 2.5.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/xiaohui-zhangxh/scws"
  # spec.metadata["changelog_uri"] = ""

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject do |f|
      (f == __FILE__) || f.match(%r{\A(?:(?:bin|test|spec|features)/|\.(?:git|travis|circleci)|appveyor)})
    end
  end
  spec.extensions = %w[ext/scws4r/extconf.rb]
  spec.require_paths = ["lib"]
end
