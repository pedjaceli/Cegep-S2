<?php 
require_once 'login.php'; 

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// JUSTE ÉDITER LA LIGNE SUIVANTE POUR LES EXERCICES
$sql = "SELECT nom, courriel FROM utilisateurs LIMIT 10";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

$stmt = $pdo->query($sql);
$resultats = $stmt->fetchAll();
$nombre_resultats = count($resultats);

// Coloration de SQL, sans dépasser!
function highlight_sql($sql) {
    $keywords = ['SELECT', 'FROM', 'WHERE', 'LIMIT', 'ORDER BY', 'INSERT', 'UPDATE', 'DELETE', 'JOIN', 'ON', 'AS'];
    foreach ($keywords as $word) {
        $sql = preg_replace("/\b($word)\b/i", "<span class='sql-keyword'>$1</span>", $sql);
    }
    return $sql;
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AlloBD</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>

<div class="app-window">
    
    <div class="window-header">
        <div class="window-controls">
            <div class="dot red"></div>
            <div class="dot yellow"></div>
            <div class="dot green"></div>
        </div>
        <div class="window-title">
            Connexion sur : <?php echo htmlspecialchars($db); ?>
        </div>
    </div>

    <div class="window-body">
        
        <div class="editor-container">
            <div class="sql-code">
                <?php echo highlight_sql(htmlspecialchars($sql)); ?><span style="color:var(--text-muted)">;</span>
            </div>
        </div>

        <div class="results-section">
            <div class="results-header">
                <h2>Résultats de la requête</h2>
                <span class="record-count"><?php echo $nombre_resultats; ?> ligne(s) retournée(s)</span>
            </div>

            <div class="table-wrapper">
                <?php if ($resultats): ?>
                    <table>
                        <thead>
                            <tr>
                                <?php foreach (array_keys($resultats[0]) as $colonne): ?>
                                    <th><?php echo htmlspecialchars(str_replace('_', ' ', $colonne)); ?></th>
                                <?php endforeach; ?>
                            </tr>
                        </thead>
                        <tbody>
                            <?php foreach ($resultats as $rangee): ?>
                                <tr>
                                    <?php foreach ($rangee as $cle => $valeur): ?>
                                        <td>
                                            <?php 
                                                if (strtolower($cle) === 'id') {
                                                    echo '<span class="id-badge">#' . htmlspecialchars($valeur) . '</span>';
                                                } else {
                                                    echo htmlspecialchars((string)$valeur);
                                                }
                                            ?>
                                        </td>
                                    <?php endforeach; ?>
                                </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                <?php else: ?>
                    <div style="padding: 2rem; text-align: center; color: var(--text-muted);">
                        Aucune donnée trouvée ou table vide.
                    </div>
                <?php endif; ?>
            </div>
        </div>
        
    </div>
</div>

</body>
</html>