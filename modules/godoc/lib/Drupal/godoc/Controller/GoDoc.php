<?php
namespace Drupal\godoc\Controller;

class GoDoc {
  public function pageCallback($part = 'index') {
    switch ($part) {
      case 'index':
        $controller = strtoupper('index');
        break;

      case 'roles':
        $controller = strtoupper('role');
        break;

      case 'content-types':
        $controller = strtoupper('type');
        break;

      case 'views':
        $controller = strtoupper('view');
        break;

      case 'contexts':
        $controller = strtoupper('context');
        break;

      case 'modules':
        $controller = strtoupper('module');
        break;
    }

    if (!empty($controller)) {
      $arguments = func_get_args();
      $options['ttl'] = '+ 30 minutes';
      $options['cache_id'] = 'godoc:pageCallback:' . md5(serialize($arguments));
      $options['tags'] = array('godoc', $controller);

      return go_cache($options, function() use ($controller, $arguments) {
        $controller = "Drupal\godoc\Controller\{$controller}";
        $controller = new $controller();
        return call_user_method_array('pageCallback', $controller, $arguments);
      });
    }
  }
}
