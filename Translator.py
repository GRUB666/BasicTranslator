import requests 
import json
 
def getTranslate(text, lang_code = 'en-ru'):
    url = 'https://translate.yandex.net/api/v1.5/tr.json/translate?'
    key = 'trnsl.1.1.20190227T075339Z.1b02a9ab6d4a47cc.f37d50831b51374ee600fd6aa0259419fd7ecd97'
    lang = lang_code; 
    r = requests.post(url, data={'key': key, 'text': text, 'lang': lang})  
    return json.loads(r.text)['text'][0]

txt = input();
lang = input();

print(getTranslate(txt, lang))
input();

