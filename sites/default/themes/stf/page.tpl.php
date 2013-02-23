<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language ?>" xml:lang="<?php print $language ?>">
<head>
  <title><?php print $head_title ?></title>
  <?php print $styles ?>
  <?php print $head ?>
  <?php print $scripts ?>
  <!--[if IE 6]>
    <style type="text/css" media="all">@import "<?php echo base_path() . path_to_theme(); ?>/ie6.css";</style>
  <![endif]-->
</head>
<body>

<div id="header">
  <div id="logo">
    <?php if ($logo) { ?><a id="logo-link" href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><img src="<?php print $logo ?>" alt="<?php print t('Home') ?>" /></a><?php } ?>
  </div>
  <?php if ($site_name) { ?><h1 class='site-name'><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><?php print $site_name ?></a></h1><?php } ?>
  <?php if ($site_slogan) { ?><div class='site-slogan'><?php print $site_slogan ?></div><?php } ?>
    <?php if (isset($primary_links)) { ?><div id="primarylinks"><?php print theme('links', $primary_links, array('class' =>'links', 'id' => 'navlist')) ?></div><?php } ?>
  <?php print $breadcrumb; ?>
  <?php if ($search_box) : ?>
    <div class="search-box"><?php print $search_box; ?></div>
  <?php endif; ?>
  <div class="marketing">
    <a href="http://www.facebook.com/groups/103312886459880/" title="Visit our Facebook Group" target="_blank"><img src="/webb/sites/default/themes/stf/facebook.png" alt="Facebook" /></a>
    <a href="http://twitter.com/StarfleetSTF" title="Visit our Twitter Page" target="_blank"><img src="/webb/sites/default/themes/stf/twitter.png" alt="Twitter" /></a>
  </div>
</div>

<div id="content" class="container">
  <?php if ($sidebar_left) : ?>
    <div id="sidebar-left" class="sidebar">
      <?php print $sidebar_left ?>
    </div>
  <?php endif; ?>
    
  <div id="body_pane">
    <?php if(!empty($tabs)) { ?><div class="tabs"><?php print $tabs ?></div><?php }?>
    <div id="main" class="sb <?php if($is_front){ print "main-front"; }?>">
      <?php if (!empty($mission)) : ?>
        <div class="mission-header"><h2>Welcome to STF</h2></div><div class="mission-statement"><?php print $mission; ?></div>
      <?php endif; ?>
      <h1 class="title"><?php print $title ?></h1>
      <?php print $help ?>
      <?php print $messages ?>
      <?php print $content; ?>
      <?php print $feed_icons; ?>
      <span class="corner-top-left corner"></span>
      <span class="corner-top-right corner"></span>
      <span class="corner-bottom-left corner"></span>
      <span class="corner-bottom-right corner"></span>
    </div>
  </div>
  
  <div id="footer">
    <div>
      <?php print $footer_message ?>
      &nbsp;&nbsp;&nbsp;&nbsp;
      <?php if (isset($secondary_links)) { ?><?php print theme('links', $secondary_links, array('class' =>'links', 'id' => 'subnavlist')) ?><?php } ?>
    </div>
  </div>
</div>

<?php print $closure ?>
</body>
</html>


