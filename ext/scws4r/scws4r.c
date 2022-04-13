#include "scws4r.h"

int scws4r_min(int x, int y){
  return (x < y) ? x : y;
}

struct rb_scws_malloc{
  void *engine;
};

static void
rb_scws_free(void *p) {
  struct rb_scws_malloc *ptr = p;
	free(ptr->engine);
}

static VALUE
rb_scws_alloc(VALUE klass) {
  VALUE obj;
  struct rb_scws_malloc *ptr;

  obj = Data_Make_Struct(klass, struct rb_scws_malloc, NULL, rb_scws_free, ptr);

  ptr->engine  = NULL;

  return obj;
}

static VALUE
rb_scws_init(VALUE self){
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_t s;
	s = scws_new();
	ptr->engine = s;
	scws_set_charset(ptr->engine, "utf8");
	return self;
}

static VALUE
rb_scws_set_charset(VALUE self, VALUE r_charset){
	Check_Type(r_charset, T_STRING);
	char* charset = RSTRING_PTR(r_charset);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_charset(ptr->engine, charset);
}

static VALUE
rb_scws_set_dic(VALUE self, VALUE r_path, VALUE r_mode){
	Check_Type(r_path, T_STRING);
	Check_Type(r_mode, T_FIXNUM);
	char* path = RSTRING_PTR(r_path);
  int mode = NUM2INT(r_mode);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	int ret = scws_set_dict(ptr->engine, path, mode);
  return ret == 0;
}

static VALUE
rb_scws_add_dic(VALUE self, VALUE r_path, VALUE r_mode){
	Check_Type(r_path, T_STRING);
	Check_Type(r_mode, T_FIXNUM);
	char* path = RSTRING_PTR(r_path);
  int mode = NUM2INT(r_mode);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	int ret = scws_add_dict(ptr->engine, path, mode);
  return ret == 0;
}

static VALUE
rb_scws_set_rule(VALUE self, VALUE r_path){
	Check_Type(r_path, T_STRING);
	char* path = RSTRING_PTR(r_path);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_rule(ptr->engine, path);
}

static VALUE
rb_scws_set_ignore(VALUE self, VALUE r_yes){
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_rule(ptr->engine, RTEST(r_yes) ? 1 : 0);
}

static VALUE
rb_scws_set_multi(VALUE self, VALUE r_mode){
	Check_Type(r_mode, T_FIXNUM);
  int mode = NUM2INT(r_mode);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_multi(ptr->engine, mode);
}

static VALUE
rb_scws_set_duality(VALUE self, VALUE r_yes){
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_duality(ptr->engine, RTEST(r_yes) ? 1 : 0);
}

static VALUE
rb_scws_set_debug(VALUE self, VALUE r_yes){
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_set_debug(ptr->engine, RTEST(r_yes) ? 1 : 0);
}

static VALUE
rb_scws_send_text(VALUE self, VALUE r_text){
	Check_Type(r_text, T_STRING);
	char* text = RSTRING_PTR(r_text);
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_send_text(ptr->engine, text, strlen(text));
	scws_res_t res, cur;
	VALUE result;
	result = rb_ary_new();
	rb_encoding *encoding = rb_utf8_encoding();

	while (res = cur = scws_get_result(ptr->engine))
  {
    while (cur != NULL)
    {
			VALUE item;
			VALUE apart;
			item = rb_hash_new();
			rb_hash_aset(item, rb_str_new2("offset"), INT2NUM(cur->off));
			rb_hash_aset(item, rb_str_new2("idf"), rb_float_new(cur->idf));
			rb_hash_aset(item, rb_str_new2("length"), INT2NUM(cur->len));
			rb_hash_aset(item, rb_str_new2("text"), rb_enc_str_new(text + cur->off, cur->len, encoding));
			rb_hash_aset(item, rb_str_new2("attr"), rb_str_new2(cur->attr));
			rb_ary_push(result, item);
      cur = cur->next;
    }
    scws_free_result(res);
  }
	return result;
}

static VALUE
rb_scws_get_tops(int argc, VALUE *argv, VALUE self){
  VALUE r_text, r_limit, r_attrs;
  rb_scan_args(argc, argv, "21", &r_text, &r_limit, &r_attrs);
	Check_Type(r_text, T_STRING);
	Check_Type(r_limit, T_FIXNUM);
	char* text = RSTRING_PTR(r_text);
	char limit = NUM2INT(r_limit);
	char* attrs;
  if (T_NIL == TYPE(r_attrs)){
    attrs = NULL;
  }else{
    Check_Type(r_attrs, T_STRING);
    attrs = RSTRING_PTR(r_attrs);
  }
	struct rb_scws_malloc *ptr;
	Data_Get_Struct(self, struct rb_scws_malloc, ptr);
	scws_send_text(ptr->engine, text, strlen(text));
	scws_top_t cur;
	VALUE result;
	result = rb_ary_new();
	rb_encoding *encoding = rb_utf8_encoding();

  cur = scws_get_tops(ptr->engine, limit, attrs);
  while (cur != NULL)
  {
    VALUE item;
    VALUE apart;
    item = rb_hash_new();
    rb_hash_aset(item, rb_str_new2("times"), INT2NUM(cur->times));
    rb_hash_aset(item, rb_str_new2("weight"), rb_float_new(cur->weight));
    rb_hash_aset(item, rb_str_new2("word"), rb_enc_str_new(cur->word, strlen(cur->word), encoding));
    rb_hash_aset(item, rb_str_new2("attr"), rb_str_new(cur->attr, scws4r_min(strlen(cur->attr), 2)));
    rb_ary_push(result, item);
    cur = cur->next;
  }
  scws_free_tops(cur);
	return result;
}

void Init_scws4r(void){
	VALUE cScws;

  cScws = rb_define_class("Scws4r", rb_cObject);
	rb_define_alloc_func(cScws, rb_scws_alloc);
  rb_define_method(cScws, "initialize", rb_scws_init, 0);
  rb_define_method(cScws, "charset=", rb_scws_set_charset, 1);
  rb_define_method(cScws, "set_dic", rb_scws_set_dic, 2);
  rb_define_method(cScws, "add_dic", rb_scws_add_dic, 2);
  rb_define_method(cScws, "set_rule", rb_scws_set_rule, 1);
  rb_define_method(cScws, "punctuation_ignore=", rb_scws_set_ignore, 1);
  rb_define_method(cScws, "multi=", rb_scws_set_multi, 1);
  rb_define_method(cScws, "duality=", rb_scws_set_duality, 1);
  rb_define_method(cScws, "debug=", rb_scws_set_debug, 1);
  rb_define_method(cScws, "split", rb_scws_send_text, 1);
  rb_define_method(cScws, "tops", rb_scws_get_tops, -1);
  rb_define_const(cScws, "XDICT_XDB", INT2FIX(SCWS_XDICT_XDB));
  rb_define_const(cScws, "XDICT_MEM", INT2FIX(SCWS_XDICT_MEM));
  rb_define_const(cScws, "XDICT_TXT", INT2FIX(SCWS_XDICT_TXT));
  rb_define_const(cScws, "MULTI_SHORT", INT2FIX(SCWS_MULTI_SHORT));
  rb_define_const(cScws, "MULTI_DUALITY", INT2FIX(SCWS_MULTI_DUALITY));
  rb_define_const(cScws, "MULTI_ZMAIN", INT2FIX(SCWS_MULTI_ZMAIN));
  rb_define_const(cScws, "MULTI_ZALL", INT2FIX(SCWS_MULTI_ZALL));
}
