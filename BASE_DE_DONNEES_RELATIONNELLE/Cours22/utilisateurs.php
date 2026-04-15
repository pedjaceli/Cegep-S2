<?php 
require_once 'login.php'; 
$sql = "SELECT nom, courriel, niveau FROM utilisateurs ORDER BY nom ASC";
$stmt = $pdo->query($sql);
$utilisateurs = $stmt->fetchAll();
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Annuaire - AlloBD</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>

<div class="app-window">
    <div class="window-header">
        <div class="window-controls">
            <div class="dot red"></div><div class="dot yellow"></div><div class="dot green"></div>
        </div>
        <div class="window-title">Explorateur d'utilisateurs</div>
    </div>

    <div class="window-body">
        <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom: 2rem;">
            <h2 style="font-weight: 300; font-size: 1.8rem;">Répertoire des Membres</h2>
            <div style="background:rgba(56,189,248,0.1); color:var(--accent-glow); padding:5px 15px; border-radius:20px; font-size:0.8rem; font-weight:600; border:1px solid rgba(56,189,248,0.2);">
                <?php echo count($utilisateurs); ?> membres
            </div>
        </div>

        <div class="users-grid">
            <?php foreach ($utilisateurs as $u): 
                $initiale = mb_strtoupper(mb_substr(trim($u['nom']), 0, 1, 'UTF-8'), 'UTF-8');
                $niveauClass = strtolower(trim($u['niveau']));
            ?>
                <div class="user-card">
                    <div class="user-bubble"><?php echo $initiale; ?></div>
                    <div class="user-info">
                        <div class="user-name"><?php echo htmlspecialchars($u['nom']); ?></div>
                        <div class="user-email"><?php echo htmlspecialchars($u['courriel']); ?></div>
                        <span class="badge <?php echo $niveauClass; ?>"><?php echo htmlspecialchars($u['niveau']); ?></span>
                    </div>
                </div>
            <?php endforeach; ?>
        </div>
    </div>
</div>

</body>
</html>