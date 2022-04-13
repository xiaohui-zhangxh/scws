# frozen_string_literal: true

require_relative "scws4r/version"
require 'scws4r/scws4r'

class Scws4r
  def load_defaults
    set_dic File.expand_path('../defaults/dict.utf8.xdb', __dir__), Scws4r::XDICT_XDB | Scws4r::XDICT_MEM
    set_rule File.expand_path('../defaults/rules.utf8.int', __dir__)
  end

  def split_to_tsvector(text)
    split(text)
  end
end
