Features

1. Autoloader — @see go_autoload()

  - To disable this feature, in settings.php, define GO_DISABLE_AUTOLOAD constant.
  - Run faster with APC extension enabled.

2. go_cache()

  Without go_cache()

    function your_data_provider($reset = FALSE) {
      $cache_id = '…';
      $bin = 'bin';
      $expire = strtotime('+ 15 minutes');

      if (!$reset && $cache = cache_get($cache_id, $bin)) {
        return $cache->data;
      }

      $data = your_logic();

      cache_set($data, $cache_id, $bin, $expire);

      return $data;
    }

  With go_cache(), your logic becomes cleaner:

    function your_data_provider() {
      return your_logic();
    }

    $data = go_cache(array('cache_id' => '…'), 'your_data_provider');

3. Useful drush commands:

  drush godl ckeditor
  drush godl jquery.cycle
  drush godl colorbox
  drush go-hipchat room_id 'Message to be sent…'

4. Back ported some Components from Drupal 8

  - \Drupal\Component\Uuid
  - \DRupal\Core\KeyValueStore

5. insert google analytics code into footer page every page
  - add function go_google_analytics_code_insert, go_analytics_script_code and go_init implements hook_init() into go.module
  - go_analytics_script_code Provide google analytics code
  - go_google_analytics_code_insert will insert javascript code into footer every page be call on go_init()
  - class GoGoogleAnalyticsTestCase new added in go.test