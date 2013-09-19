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

    …

  drush godl jquery.cycle

    …

  drush godl colorbox

    …

  drush go-hipchat room_id 'Message to be sent…'

    …

  drush golive --cache=1 --js=1 --update=1

    This is wrapper command for useful auto configuration for live site:
      - Enable page/block caching
      - Enable js/css aggregation
      - Disable UI modules (context, views, rules, …)
      - Enable update.module
      - drush help golive for more informations.

4. Back ported some Components from Drupal 8

  - \Drupal\Component\Uuid
  - \Drupal\Core\KeyValueStore

5. Simple Google Analytics integration

  In settings.php configure your Google Analytics code by adding this line:

    define('GO_GOOGLE_ANALYTICS', 'UA-****');

6. Simple 403/404 handler:

  - On 403, redirect user to login page.
  - On 404, redirect user to search page.

  To enable this feature. Just go to your settings.php add these lines:

    define('GO_403', 1);
    define('GO_404', 1);
    // or
    define('GO_404', 'site-content');

7. Created new golive command

   Used command: drush golive --cache=1 --js=1 --update=1
   Please run command drush golive --help for help

No more needed modules:

  - login_redirect
  - google_analytics
  - …
